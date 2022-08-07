#include <stdio.h>
#include <omp.h> 

int main(int argc, char* argv[])
{

 int tid, nthreads; 

#pragma omp parallel private(tid)
{
  /* Get thread ID */
  tid=omp_get_thread_num();
  /* Get number of threads */
  nthreads = omp_get_num_threads();

  printf("Hello, I am thread id %d of %d.\n ", tid, nthreads);

}
  return 0;
}

