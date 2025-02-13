#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define PATCH_SIZE 1024    // Elements per patch
#define NUM_PATCHES 1000   // Total number of patches
#define OPS_PER_ELEMENT 2  // Operations per element (simple 2x scaling)

// Naive approach using OpenMP map clauses
void process_patches_naive(double** patches) {
    #pragma omp parallel for
    for (int i = 0; i < NUM_PATCHES; i++) {
        double* patch = patches[i];
        
        // Transfer data to GPU
        #pragma omp target enter data map(to: patch[0:PATCH_SIZE])
        
        // Execute kernel
        #pragma omp target teams distribute parallel for
        for (int j = 0; j < PATCH_SIZE; j++) {
            patch[j] *= 2.0;  // Simple computation
        }
        
        // Transfer data back
        #pragma omp target exit data map(from: patch[0:PATCH_SIZE])
    }
}

// Optimized host-managed memory approach
void process_patches_optimized(double** patches) {
    // Pre-allocate GPU memory for all patches
    const size_t total_size = NUM_PATCHES * PATCH_SIZE * sizeof(double);
    double* gpu_mem = omp_target_alloc(total_size, omp_get_default_device());

    #pragma omp parallel for
    for (int i = 0; i < NUM_PATCHES; i++) {
        // Copy to GPU (host -> device)
        omp_target_memcpy(
            gpu_mem + i*PATCH_SIZE,
            patches[i],
            PATCH_SIZE * sizeof(double),
            0, 0,
            omp_get_default_device(),
            omp_get_initial_device()
        );

        // Process on GPU
        #pragma omp target teams distribute parallel for \
            is_device_ptr(gpu_mem) nowait
        for (int j = 0; j < PATCH_SIZE; j++) {
            gpu_mem[i*PATCH_SIZE + j] *= 2.0;  // Same computation
        }

        // Copy back results (device -> host)
        omp_target_memcpy(
            patches[i],
            gpu_mem + i*PATCH_SIZE,
            PATCH_SIZE * sizeof(double),
            0, 0,
            omp_get_initial_device(),
            omp_get_default_device()
        );
    }
    omp_target_free(gpu_mem, omp_get_default_device());
}

int main() {

     // Check if a GPU is available
    int num_devices = omp_get_num_devices();
    printf("Number of available devices: %d\n", num_devices);

    if (num_devices < 1) {
        printf("No GPU devices available. Exiting.\n");
        return 1;
    }

    // Set default device to GPU (device 0)
    omp_set_default_device(0);	


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
    start = omp_get_wtime();
    process_patches_naive(patches);
    end = omp_get_wtime();
    time_naive = end - start;

    // Reset data for fair comparison
    for (int i = 0; i < NUM_PATCHES; i++) {
        for (int j = 0; j < PATCH_SIZE; j++) {
            patches[i][j] = (double)rand()/RAND_MAX;
        }
    }

    // Run and time optimized approach
    start = omp_get_wtime();
    process_patches_optimized(patches);
    end = omp_get_wtime();
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
