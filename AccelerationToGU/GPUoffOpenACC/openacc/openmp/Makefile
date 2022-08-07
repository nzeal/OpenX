PGCC  = pgcc -O3 -mp
PGF90 = pgfortran -O3 -mp

BIN = laplace2d_omp

help:
	@echo "Please specify the make target"
	@echo "make pgi_c or make pgi_f90"

pgi_c: laplace2d.c
	$(PGCC) -o $(BIN) $<

pgi_f90: laplace2d.F90
	$(PGF90) -o $(BIN) $<

clean:
	$(RM) $(BIN) 
