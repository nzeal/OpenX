#include <stdio.h> 
#include <omp.h>

int main(){
        int i, x; 
	x = 25;
	omp_set_num_threads(3);
       #pragma omp parallel for private(x)
	for (i = 0; i < 10; i++) {
	  x = i;
	  printf("Thread number: %d   x: %d\n", omp_get_thread_num(), x);
	}
	printf("x is %d\n", x);
}




