#include <stdio.h> 
#include <omp.h>

int main()
{
	const int n = 1000;
	int total = 0;
        int i;

	printf ( "\n" );
	printf ( "Check the race condition\n" );
	printf ( "  C/OpenMP version\n" );
	printf ( "\n" );
	printf ( "  Number of processors available = %d\n", omp_get_num_procs ( ) );
	printf ( "  Number of threads =              %d\n", omp_get_max_threads ( ) );
	printf ( "  ====================================\n" );

        #pragma omp parallel for  
	   for (i = 0; i < n; i++)
        #pragma omp atomic
		total = total + i;

	printf("  Total=%d (must be %d)\n", total, ((n-1)*n)/2); 

	/*Terminate.*/
 	printf ( "\n" );
  	printf ( "  Normal end of execution.\n" );

}
