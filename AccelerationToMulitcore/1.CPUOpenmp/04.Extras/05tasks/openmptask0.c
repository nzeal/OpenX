#include <stdio.h>
#include <omp.h>
int fib(int n)
{
	if (n<2) return n;
	else
	{
	int x, y;

	#pragma omp task shared(x) if(n>30) 
	x = fib(n-1); 

	#pragma omp task shared(y) if(n>30) 
	y = fib(n-2);

	#pragma omp taskwait	
	return x+y; 
	}
} 


int main()
{
  int n = 10;

  omp_set_dynamic(0);
  omp_set_num_threads(4);

  #pragma omp parallel
  {
    #pragma omp master
    printf ("fib(%d) = %d\n", n, fib(n));
  }
}
