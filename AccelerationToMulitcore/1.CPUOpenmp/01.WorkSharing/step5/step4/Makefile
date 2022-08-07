GCC  = gcc -O3 -fopenmp
GF90 = gfortran -O3 -fopenmp

BIN = binary_omp

help:
	@echo "Please specify the make target"
	@echo "make code_c or make code_f"

code_c: *.c
	$(GCC) -o $(BIN) $<

code_f: *.f90
	$(GF90) -o $(BIN) $<

clean:
	$(RM) $(BIN) 
