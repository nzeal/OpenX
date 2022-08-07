// based on https://stackoverflow.com/questions/22492886/openmp-how-to-retrieve-the-core-id-in-which-a-thread-is-running

#define _GNU_SOURCE // to import sched_getcpu from glibc when the compiler is not gcc 

#include <stdio.h>
#include <sched.h>
#include <omp.h>

int main() {
#pragma omp parallel
    printf("Thread %d is running on core %d\n", omp_get_thread_num(), sched_getcpu());
}
