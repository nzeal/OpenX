
#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include <math.h>
#include <sys/time.h>

#define PATCH_SIZE 1024    // Elements per patch
#define NUM_PATCHES 1000   // Total number of patches
#define OPS_PER_ELEMENT 2  // Operations per element (simple 2x scaling)

// Get time in seconds
double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

// Naive approach using OpenACC
void process_patches_naive(double** patches) {
    // Process each patch individually
    for (int i = 0; i < NUM_PATCHES; i++) {
        double* patch = patches[i];

        // Transfer data to GPU, process, and transfer back
        #pragma acc data copyin(patch[0:PATCH_SIZE]) copyout(patch[0:PATCH_SIZE])
        {
            #pragma acc parallel loop
            for (int j = 0; j < PATCH_SIZE; j++) {
                patch[j] *= 2.0;  // Simple computation
            }
        }
    }
}

// Optimized approach using OpenACC with properly managed device memory
void process_patches_optimized(double** patches) {
    // Allocate device memory using device pointer
    void* device_ptr = acc_malloc(NUM_PATCHES * PATCH_SIZE * sizeof(double));
    double* gpu_mem = (double*)device_ptr;
    
    if (!gpu_mem) {
        printf("Failed to allocate device memory\n");
        return;
    }
    
    // Copy and process each patch
    for (int i = 0; i < NUM_PATCHES; i++) {
        // Copy to GPU (host -> device)
        acc_memcpy_to_device(gpu_mem + i*PATCH_SIZE, patches[i], PATCH_SIZE * sizeof(double));
        
        // Process on GPU - we create a data region that points to the already-allocated memory
        #pragma acc data deviceptr(gpu_mem)
        {
            #pragma acc parallel loop
            for (int j = 0; j < PATCH_SIZE; j++) {
                gpu_mem[i*PATCH_SIZE + j] *= 2.0;
            }
        }
        
        // Copy back results (device -> host)
        acc_memcpy_from_device(patches[i], gpu_mem + i*PATCH_SIZE, PATCH_SIZE * sizeof(double));
    }
    
    // Free device memory
    acc_free(gpu_mem);
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

    // Initialize patches with random values
    double** patches = malloc(NUM_PATCHES * sizeof(double*));
    for (int i = 0; i < NUM_PATCHES; i++) {
        patches[i] = malloc(PATCH_SIZE * sizeof(double));
        for (int j = 0; j < PATCH_SIZE; j++) {
            patches[i][j] = (double)rand()/RAND_MAX;
        }
    }

    // Time measurement variables
    double start, end, time_naive, time_optimized;

    // Run and time naive approach
    start = get_time();
    process_patches_naive(patches);
    end = get_time();
    time_naive = end - start;

    // Reset data for fair comparison
    for (int i = 0; i < NUM_PATCHES; i++) {
        for (int j = 0; j < PATCH_SIZE; j++) {
            patches[i][j] = (double)rand()/RAND_MAX;
        }
    }

    // Run and time optimized approach
    start = get_time();
    process_patches_optimized(patches);
    end = get_time();
    time_optimized = end - start;

    // Calculate metrics
    const double total_ops = (double)NUM_PATCHES * PATCH_SIZE * OPS_PER_ELEMENT;
    const double total_data = (double)NUM_PATCHES * PATCH_SIZE * sizeof(double) * 2 / 1e9;

    printf("\nPerformance Results:\n");
    printf("========================================\n");
    printf("Naive Approach:\n");
    printf("  Time:       %.3f ms\n", time_naive * 1e3);
    printf("  Throughput: %.2f GOp/s\n", (total_ops/1e9)/time_naive);
    printf("  Memory BW:  %.2f GB/s\n", total_data/time_naive);

    printf("\nOptimized Approach:\n");
    printf("  Time:       %.3f ms\n", time_optimized * 1e3);
    printf("  Throughput: %.2f GOp/s\n", (total_ops/1e9)/time_optimized);
    printf("  Memory BW:  %.2f GB/s\n", total_data/time_optimized);

    printf("\nSpeedup: %.1fx\n", time_naive/time_optimized);

    // Cleanup
    for (int i = 0; i < NUM_PATCHES; i++) {
        free(patches[i]);
    }
    free(patches);

    return 0;
}
