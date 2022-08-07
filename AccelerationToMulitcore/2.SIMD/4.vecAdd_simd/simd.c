#include <stdio.h>
#include <omp.h>
#define N 100


int main()
{
	int i;
	float scale;

	float a[N];

   for (int i=0; i<N; i++)
   {
      a[i] = (float)i;
   }
   
   #pragma omp simd aligned(a:16)
   for (int i=0; i<N; i++)
	   a[i] = a[i]*scale;
   

   for ( i = 0; i < N && i < 10; i++ )
   {
    printf ( "  %2d %10.4f\n", i, a[i] );
   } 

   return 0;
}


