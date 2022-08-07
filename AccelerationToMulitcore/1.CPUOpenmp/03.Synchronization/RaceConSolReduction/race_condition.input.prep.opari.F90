
#line 1 "/gpfs/scratch/userinternal/nshukla1/Summer_School_OpenMP_2021/src/RaceCondition/RaceConSolReduction/race_condition.input.prep.f90"
# 1 "race_condition.input.F90"
# 1 "race_condition.input.F90"
# 1 "<built-in>"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "<command-line>"
# 1 "race_condition.input.F90"
# 1 "race_condition.input.F90"
# 1 "/gpfs/scratch/userinternal/nshukla1/Summer_School_OpenMP_2021/src/RaceCondition/RaceConSolReduction/race_condition.f90"
# 1 "/gpfs/scratch/userinternal/nshukla1/Summer_School_OpenMP_2021/src/RaceCondition/RaceConSolReduction/race_condition.f90"
program race_condition
      use omp_lib
      implicit none
      include 'race_condition.input.prep.f90.opari.inc'
#line 4 "/gpfs/scratch/userinternal/nshukla1/Summer_School_OpenMP_2021/src/RaceCondition/RaceConSolReduction/race_condition.f90"
      real(kind=8) :: start, finish

      integer i, n, sum

      n = 100000
      sum = 0

     ! Start timer
     call cpu_time(start)
      pomp2_num_threads = pomp2_lib_get_max_threads()
      pomp2_if = .true.
      call POMP2_Parallel_fork(opari2_region_1,&
      pomp2_if, pomp2_num_threads, pomp2_old_task, &
      opari2_ctc_1 )
#line 13 "/gpfs/scratch/userinternal/nshukla1/Summer_School_OpenMP_2021/src/RaceCondition/RaceConSolReduction/race_condition.f90"
     !$omp parallel    reduction(+:sum) &
  !$omp firstprivate(pomp2_old_task) private(pomp2_new_task) &
  !$omp num_threads(pomp2_num_threads)
      call POMP2_Parallel_begin(opari2_region_1)
      call POMP2_Do_enter(opari2_region_1, &
     opari2_ctc_1 )
#line 13 "/gpfs/scratch/userinternal/nshukla1/Summer_School_OpenMP_2021/src/RaceCondition/RaceConSolReduction/race_condition.f90"
     !$omp          do                 
     do i = 1, n-1 
     sum = sum + i
     end do
#line 17 "/gpfs/scratch/userinternal/nshukla1/Summer_School_OpenMP_2021/src/RaceCondition/RaceConSolReduction/race_condition.f90"
!$omp end do nowait
      call POMP2_Implicit_barrier_enter(opari2_region_1,&
      pomp2_old_task)
!$omp barrier
      call POMP2_Implicit_barrier_exit(opari2_region_1, pomp2_old_task)
      call POMP2_Do_exit(opari2_region_1)
      call POMP2_Parallel_end(opari2_region_1)
#line 17 "/gpfs/scratch/userinternal/nshukla1/Summer_School_OpenMP_2021/src/RaceCondition/RaceConSolReduction/race_condition.f90"
!$omp end parallel
      call POMP2_Parallel_join(opari2_region_1, pomp2_old_task)
#line 18 "/gpfs/scratch/userinternal/nshukla1/Summer_School_OpenMP_2021/src/RaceCondition/RaceConSolReduction/race_condition.f90"
     call cpu_time(finish)

     write(*,"(A)")         "-----------------------------------------"
     write(*,*)               "The total is : ",   sum, ((n-1)*n)/2
     write(*,"(A,F18.9)")        " runtime:   ",        finish-start
     write(*,"(A)")         "-----------------------------------------"

end program race_condition



      subroutine POMP2_Init_reg_kdlj9bwstvdpii_1()
         include 'race_condition.input.prep.f90.opari.inc'
         call POMP2_Assign_handle( opari2_region_1, &
         opari2_ctc_1 )
      end
