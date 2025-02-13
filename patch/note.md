# Efficient GPU Offloading with OpenMP

## Key component explained:

### Version1:: offloadPatches.c

The provided code is a C program that uses OpenMP to process patches of data on a GPU. It includes two versions of the patch processing:

- a naive version
- an improved version

Here's a brief explanation of the main components:
- compute_throughput: Calculates and prints the computation throughput in operations per second.
- memory_throughput: Calculates and prints the memory throughput in MB per second.
- process_patches_naive: Processes each patch separately on the GPU.
- process_patches_improved: Processes all patches in one GPU operation.
- main: Initializes the patches, checks for available GPU devices, and calls the naive and improved processing functions.


### Version2:: patch.c

1. Initialization: 
 - Creates NUM_PATCHES arrays of PATCH_SIZE elements
 - Fills with random values between 0 and 1

2. Naive Approach:
 - Uses OpenMP's automatic memory management (map clauses)
 - Each patch transfer and computation is handled individually
 - Suffers from repeated GPU memory allocation/deallocation

3. Optimized Approach:
 - Pre-allocates all required GPU memory upfront
 - Uses explicit memory copies (omp_target_memcpy)
 - Reuses device memory across operations
 - Uses is_device_ptr to bypass OpenMP's memory mapping
 - nowait clause enables asynchronous execution


## Outcome



## Reference 
A. Bhatele et al. (Eds.): ISC High Performance 2023, LNCS 13948, pp. 65–85, 2023.
https://doi.org/10.1007/978-3-031-32041-5_4


## Main findings:                                                                                                                                                                                             1. Concurrent GPU memory management via OpenMP's map clauses causes synchronization issues and performance loss.

2. Host-managed GPU memory (pre-allocated and reused) mitigates this bottleneck.
                                                                                                       3. Batching small patches into larger kernels improves GPU utilization.
                                                                                                       4. Unified memory underperforms compared to manual management due to latency in data migration.
                                                                                                  

The paper addresses performance bottlenecks in GPU offloading for a hyperbolic finite volume solver     using OpenMP on dynamically adaptive meshes. The key issue stems from OpenMP's GPU memory manageme    nt (map clauses), which introduces synchronization overhead when multiple CPU threads concurrently     offload tasks. This leads to significant slowdowns due to frequent GPU memory allocations/deallocat    ions.
