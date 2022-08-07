! =========================
!  Hello world
! =========================
program helloWorld_omp_parallel

  USE omp_lib

  implicit none 
  INTEGER :: nthreads=4
  integer :: tid
  
  CALL OMP_SET_NUM_THREADS(nthreads)

  !$omp parallel
  tid = OMP_GET_THREAD_NUM()
  print *, "Hello World from thread = ", tid, " with ", OMP_GET_NUM_THREADS(), " threads" 
  !$omp end parallel

  PRINT *, "all done, with hopefully ",nthreads," threads"

end program helloWorld_omp_parallel
