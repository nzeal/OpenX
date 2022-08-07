#include <stdio.h>
#include <omp.h> 

int main(int argc, char* argv[])
{
  int nthreads = 4;

#pragma omp parallel
{
  int id = omp_get_thread_num();

  printf("Hello(%d)\n",id);
  printf("world(%d)\n",id);
}
  return 0;
}


