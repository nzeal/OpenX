      INTEGER( KIND=8 ) :: opari2_region_1

      CHARACTER (LEN=304), parameter :: opari2_ctc_1 =&
      "301*regionType=paralleldo*sscl=/gpfs/scratch/userinternal"//&
      "/nshukla1/Summer_School_OpenMP_2021/src/RaceCondition/Ra"//&
      "ceConSolReduction/race_condition.f90:13:13*escl=/gpfs/sc"//&
      "ratch/userinternal/nshukla1/Summer_School_OpenMP_2021/sr"//&
      "c/RaceCondition/RaceConSolReduction/race_condition.f90:1"//&
      "7:17*hasReduction=1**"

      common /cbkdlj9bwstvdpii/ opari2_region_1

      integer ( kind=4 ) :: pomp2_lib_get_max_threads
      logical :: pomp2_test_lock
      integer ( kind=4 ) :: pomp2_test_nest_lock
      integer ( kind=8 ) :: pomp2_old_task, pomp2_new_task 
      logical :: pomp2_if 
      integer ( kind=4 ) :: pomp2_num_threads 
