! =========================
!  Get thread no. and id
! =========================

program helloWorld

      use omp_lib

      implicit none
      integer :: tid, nthreads

      !$omp parallel private(tid)

      !Get and print thread id
      tid = OMP_GET_THREAD_NUM()
      nthreads = OMP_GET_NUM_THREADS()
      
      print *, "Hello World! I'm tid", tid, "in nthreads", nthreads
          
      !$omp end parallel 
end program helloWorld
