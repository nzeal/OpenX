! =========================
!  Race condition
! =========================

program helloWorld
 
  use omp_lib
  implicit none

  integer :: num_threads = 4
  integer :: thread_num = 0

  !$ call omp_set_num_threads(num_threads)
  print*, "Hello world!"
  print*, "Number of threads:",num_threads

  !$omp parallel
    !$omp critical
      !$ thread_num = omp_get_thread_num()
      print *, "Hello world!", thread_num
    !$omp end critical
  !$omp end parallel

end program helloWorld
