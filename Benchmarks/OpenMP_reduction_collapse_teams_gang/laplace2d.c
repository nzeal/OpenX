#include <math.h>
#include <string.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "nvtx.h"

#define NN 4096
#define NM 4096

double A[NN][NM];
double Anew[NN][NM];

int main() {

    int n = NN;
    int m = NM;
    int iter_max = 100;
    double tol = 1.0e-6;

    double error = 1.0;
    int iter = 0;
    int i,j;
    struct timeval temp_1, temp_2;
    double ttime=0.;

  mynvtxstart_("memset");
      memset(A, 0, n * m * sizeof(double));
      memset(Anew, 0, n * m * sizeof(double));
   mynvtxstop_();

mynvtxstart_("host_init");
    for (j = 0; j < n; j++)
    {
        A[j][0]    = 1.0;
        Anew[j][0] = 1.0;
    }

    printf("Jacobi relaxation Calculation: %d x %d mesh\n", n, m);

    gettimeofday(&temp_1, (struct timezone*)0);
 mynvtxstop_();

#pragma omp target enter data map(to:A) map(alloc:Anew)
 while ( error > tol && iter < iter_max )
    {
        error = 0.0;



 mynvtxstart_("kernel_1");
#pragma omp target teams distribute parallel for simd num_teams(512) thread_limit(512) reduction(max:error) collapse(2)
        for( j = 1; j < n-1; j++) {
            for( i = 1; i < m-1; i++ ) {
                Anew[j][i] = 0.25 * ( A[j][i+1] + A[j][i-1]
                                    + A[j-1][i] + A[j+1][i]);
                error = fmax( error, fabs(Anew[j][i] - A[j][i]));
            }
        }
 mynvtxstop_();

 mynvtxstart_("kernel_2");
#pragma omp target teams distribute parallel for simd num_teams(512) thread_limit(512) collapse(2)
        for( j = 1; j < n-1; j++) {
            for( i = 1; i < m-1; i++ ) {
                A[j][i] = Anew[j][i];
            }
        }
 mynvtxstop_();

	
        if(iter % 10 == 0) printf("%5d, %0.8lf\n", iter, error);
        iter++;
    }
    #pragma omp target exit data map(from:A)

    gettimeofday(&temp_2, (struct timezone*)0);
    ttime = 0.000001*((temp_2.tv_sec-temp_1.tv_sec)*1.e6+(temp_2.tv_usec-temp_1 .tv_usec));

    printf("Elapsed time (s) = %.2lf\n", ttime);
    printf("Stopped at iteration: %u\n", iter);

    return 0;

}
