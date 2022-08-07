GCC = gcc
GF90 = gfortran

XFLAG = -fopenmp

BIN = binary_omp

help:
	@echo -e "make ccode\tC code\tcompiled with gcc"
	@echo -e "make fcode\tFortran code \tcompiled with gfortran"

ccode: *.c
	$(GCC) $(XFLAG) -o $(BIN) $<

fcode: *f90
	$(GF90) $(XFLAG) -o $(BIN) $<

clean:
	$(RM) $(BIN)

