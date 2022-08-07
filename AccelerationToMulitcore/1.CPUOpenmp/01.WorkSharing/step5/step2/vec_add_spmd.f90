program vecAdd
  
  use omp_lib

  implicit none
  real(kind=8) :: start, finish

  integer :: N=1e8
  real(kind=8), allocatable :: A(:), B(:), C(:)
  integer :: i
  integer :: tid, nthreads  
  
  ! Allocate memory
  allocate( A(N) , B(N) , C(N) )

    ! Initilise data
  do i = 1, N
    A(i) = i*1.0_8
    B(i) = A(i)
  end do

  ! Start timer
  call cpu_time(start)

  ! Open parallel region
  ! tid variable must be private to each thread
  !$omp parallel private(tid)

  ! Get thread number
  tid = omp_get_thread_num()

  ! Get total number of threads
  nthreads = omp_get_num_threads()

  ! Vector addition
  ! Share iteration space based on thread ID
  do i = 1+(tid*N/nthreads), (tid+1)*N/nthreads
    C(i) = A(i) + B(i)
  end do

  ! End parallel region
  !$omp end parallel

  call cpu_time(finish)

  ! Print result
  write(*,"(A)")         "------------------------------------"
  write(*,"(A,F10.3)")   "runtime:  ", finish-start
  write(*,"(A)")         "------------------------------------"

  deallocate(A,B, C)
end program vecAdd

