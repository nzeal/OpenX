#!/bin/bash





        nsys profile --trace=cuda,nvtx,mpi,openacc,openmp --cuda-memory-usage=true $*



