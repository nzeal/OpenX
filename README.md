## Parallel computation on the CPU and GPU: structure and application 

	Nitin Shukla
	CINECA, Bologna, Italy 
   
# -------------------------------------------------

Topics that we covered

1. Why Parallel computers are here to stay 

2. Parallelization on CPU 
   a. Parallel construct 
   b. Synchronization construct 
   c. Worksharing construct
   d. Data sharing
   e. Exercises 
      Total 4 with src code

3. Single instruction multiple data (SIMD)

4. Introduction to Hetrogenous system (GPU) 

5. OpenACC offloadings 
  a. Data movement 
  b. Loop parallelisms 

5. OpenMP Offloadings 
  a. Target construct
  b. The map clause
  c. Target Teams construct 
  d. Nowait clauses 
  e. Distributed construct
  f. 5th and 6th Exercises
  
  Benchmark 
# -------------------------------------------------

## Authors and acknowledgment
Thanks to:
 1. Tim Mattson (Intel)
 2. Tom Deakin (University of Bristol)
 3. Michael Klemm (AMD)
 4. Jeff Larkin (Nvidia)
 5. Manuel Arenaz (NERSC)
 6. Luca and Sergio (CINECA)
and many others 
OpenMP 5.0.1 specification and examples https://www.openmp.org/resources/ 

## Feedback 
----------------------------------------
We welcome constructive feedback to improve the quality of this work. So if you have one contact me:
n.shukla@cineca.it
