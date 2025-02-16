#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include <sys/time.h>

#define NUM_PATCHES 1024
#define PATCH_SIZE 256
#define ELEMENTS_PER_PATCH (PATCH_SIZE)

// Get time in seconds
double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

/**
 * @brief Computes and prints the computation throughput.
 *
 * @param start_time The start time of the computation.
 * @param end_time The end time of the computation.
 * @param total_operations The total number of operations performed.
 */
void compute_throughput(double start_time, double end_time, double total_operations) {
    double elapsed_time = end_time - start_time;
    double throughput = total_operations / elapsed_time;  // operations per second
    printf("Computation throughput: %.2f operations/sec\n", throughput);
}

/**
 * @brief Computes and prints the memory throughput.
 *
 * @param start_time The start time of the memory operation.
 * @param end_time The end time of the memory operation.
 * @param total_bytes The total number of bytes transferred.
 */
void memory_throughput(double start_time, double end_time, size_t total_bytes) {
    double elapsed_time = end_time - start_time;
    double throughput = total_bytes / elapsed_time / (1024 * 1024);  // MB/sec
    printf("Memory throughput: %.2f MB/sec\n", throughput);
}

/**
 * @brief Processes each patch separately on the GPU (naive version).
 *
 * @param patches_host Pointer to the host memory containing the patches.
 */
void process_patches_naive(float *patches_host) {
    double start_time = get_time();
    size_t total_bytes = NUM_PATCHES * PATCH_SIZE * sizeof(float) * 2; // Account for both directions

    // Process each patch individually
    for (int i = 0; i < NUM_PATCHES; i++) {
        float *current_patch = patches_host + (i * PATCH_SIZE);

        #pragma acc data copy(current_patch[0:PATCH_SIZE])
        {
            #pragma acc parallel loop
            for (int j = 0; j < PATCH_SIZE; j++) {
                current_patch[j] *= 2.0f;
            }
        }
    }

    double end_time = get_time();
    printf("\nNaive Version:\n");
    printf("Time taken: %.5f seconds\n", end_time - start_time);
    compute_throughput(start_time, end_time, NUM_PATCHES * PATCH_SIZE);
    memory_throughput(start_time, end_time, total_bytes);
}

/**
 * @brief Processes all patches in one GPU operation (improved version).
 *
 * @param patches_host Pointer to the host memory containing the patches.
 */
void process_patches_improved(float *patches_host) {
    double start_time = get_time();
    size_t total_bytes = NUM_PATCHES * PATCH_SIZE * sizeof(float) * 2; // Account for both directions

    // Allocate and transfer all data at once
    #pragma acc data copy(patches_host[0:NUM_PATCHES*PATCH_SIZE])
    {
        // Process all patches in parallel on the GPU
        #pragma acc parallel loop collapse(2)
        for (int i = 0; i < NUM_PATCHES; i++) {
            for (int j = 0; j < PATCH_SIZE; j++) {
                int idx = i * PATCH_SIZE + j;
                patches_host[idx] *= 2.0f;
            }
        }
    }

    double end_time = get_time();
    printf("\nImproved Version:\n");
    printf("Time taken: %.5f seconds\n", end_time - start_time);
    compute_throughput(start_time, end_time, NUM_PATCHES * PATCH_SIZE);
    memory_throughput(start_time, end_time, total_bytes);
}

int main() {
    // Check if a GPU is available
    int num_devices = acc_get_num_devices(acc_device_nvidia);
    printf("Number of available devices: %d\n", num_devices);

    if (num_devices < 1) {
        printf("No GPU devices available. Exiting.\n");
        return 1;
    }

    // Set default device to GPU (device 0)
    acc_set_device_num(0, acc_device_nvidia);

    float *patches_host = (float *)malloc(NUM_PATCHES * PATCH_SIZE * sizeof(float));
    if (!patches_host) {
        printf("Failed to allocate host memory\n");
        return 1;
    }

    // Initialize patches
    for (int i = 0; i < NUM_PATCHES * PATCH_SIZE; i++) {
        patches_host[i] = i * 0.5f;
    }

    printf("\nPerformance Results:\n");
    printf("========================================\n");

    printf("Naive Approach:\n");
    // Process patches with naive approach
    process_patches_naive(patches_host);

    // Reset patches
    for (int i = 0; i < NUM_PATCHES * PATCH_SIZE; i++) {
        patches_host[i] = i * 0.5f;
    }

    printf("\nOptimized Approach:\n");
    // Process patches with improved approach
    process_patches_improved(patches_host);

    free(patches_host);
    return 0;
}
