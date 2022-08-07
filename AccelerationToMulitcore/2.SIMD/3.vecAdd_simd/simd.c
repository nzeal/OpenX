#include <stdio.h>
#include <omp.h>
#define N 100


int main()
{
	int i, j = 0;
	int offset;

	float a[N], b[N], c[N];

// fill the arrays
   for (int i=0; i<N; i++)
   {
      a[i] = (float)i;
      b[i] = 2.0*(float)i;
      c[i] = 0.0;
   }

// add two vectors
   #pragma omp simd linear(j:1)
   for (int i=offset; i<N; i+=2)
	   c[i] = a[j++] + b[i];
 
   
  for ( i = offset; i < N && i < 10; i++ )
  {
    printf ( "  %2d %10.4f\n", i, c[i] );
  } 

   return 0;
}


