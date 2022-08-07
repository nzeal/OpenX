GCC = gcc -fopenmp
FOR = gfortran -fopenmp

BIN = binary

help:
	@echo "Please specify the make target"
	@echo "make mpc or make mpf"
mpc: *.c
	$(GCC) -o $(BIN) $<
mpf: *.f90
	$(FOR) -o $(BIN) $<
clean:
	$(RM) $(BIN) 

