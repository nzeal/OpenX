 <p align="center">

 </p>
 
 <h2 align="center"> Parallel computation on the CPU and GPU: structure and application </h2>

<p align="center"> Open<b>X</b> { <b> X = MP/ACC </b> } Directives </p>
  


<br>

### Objective

```
.
├── AccelerationToMulitcore
│   ├── 1.CPUOpenmp
│   ├── 2.SIMD
│   └── 3.AffinityOpenMP
├── AccelerationToGU
│   ├── GPUoffOpenACC
│   └── GPUoffOpenMP
├── Benchmarks
│   ├── OpenACC_ganga_reduction_collapse
│   ├── OpenACC_kernels_data_optimized
│   ├── OpenAcc_reduction_collapse
│   ├── OpenMP_reduction_collapse
│   ├── OpenMP_reduction_collapse_teams_gang
│   └── openmpPerformance
├── benchmarkfig1.html
└── benchmarkfig1.png
        └── mm_matrix.cu
```

<br>

### Topics
1. OpenMP Directives
2. Single instruction multiple data (SIMD)
3. OpenACC offloadings

    a. Data movement
    b. Loop parallelisms 

4. OpenMP Offloadings

    a. Target construct
    b. The map clause
    c. Target Teams construct
    d. Nowait clauses
    e. Distributed construct

5. Benchmark  
# -------------------------------------------------

## Authors and acknowledgment
Thanks to:
 1. Tim Mattson (Intel)
 2. Tom Deakin (University of Bristol)
 3. Michael Klemm (AMD)
 4. Jeff Larkin (Nvidia)
 5. Manuel Arenaz (NERSC)
 6. Luca and Sergio (CINECA)
and many others 
OpenMP 5.0.1 specification and examples https://www.openmp.org/resources/ 

## Feedback 
----------------------------------------
To improve the quality of this work or for any suggestion contact me:
n.shukla@cineca.it
----------------------------------------
