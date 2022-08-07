#include <stdio.h> 
#include <omp.h>

int main(){
        int i, x; 
	x = 5;
	omp_set_num_threads(3);
       #pragma omp parallel for firstprivate(x)
	for (i = 0; i < 10; i++) {
          printf("Thread number: %d   x: %d\n", omp_get_thread_num(), x);
	  x = i;
	  printf("Thread number: %d   x: %d\n", omp_get_thread_num(), x);
	}
	printf("x is %d\n", x);
}
