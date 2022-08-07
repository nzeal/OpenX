FC=gcc
FFLAGS=-O3 -fopenmp 

SRC=*.c
OBJ=${SRC:.c=.o}
NAME = std.out

%.o: %.c
	$(FC) $(FFLAGS) -c $<

output: $(OBJ)
	$(FC) $(FFLAGS) -o $(NAME) $(OBJ)
	
clean: 
	@rm -f *.o *.out


