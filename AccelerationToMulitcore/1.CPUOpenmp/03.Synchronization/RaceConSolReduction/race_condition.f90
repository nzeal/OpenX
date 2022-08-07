program race_condition
      use omp_lib
      implicit none
      real(kind=8) :: start, finish

      integer i, n, sum

      n = 100000
      sum = 0

     ! Start timer
     call cpu_time(start)
     !$omp parallel do reduction(+:sum)
     do i = 1, n-1 
     sum = sum + i
     end do
     !$omp end parallel do
     call cpu_time(finish)

     write(*,"(A)")         "-----------------------------------------"
     write(*,*)               "The total is : ",   sum, ((n-1)*n)/2
     write(*,"(A,F18.9)")        " runtime:   ",        finish-start
     write(*,"(A)")         "-----------------------------------------"

end program race_condition


