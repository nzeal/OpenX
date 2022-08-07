#include <stdio.h> 
#include <omp.h>

int main(){
        int x = 4;
	omp_set_num_threads(3);
       
#pragma omp parallel private(x)
	{
	  x = 3; 
	 do
	  {
	  	int tid = omp_get_thread_num(); 
		printf("Thread number: %d   shared: x is %d\n", tid, x);
		x--; 
	  } while (x > 0);
        }
	printf("%d: last value of x: ", x);
}




