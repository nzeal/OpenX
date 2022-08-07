NVCC = pgcc

NVCCFLAGS = -O3 -mp=gpu -Minfo=accel,loop,mp

NVCCFLAGS2 = -I/cineca/prod/opt/compilers/hpc-sdk/2021/binary/Linux_ppc64le/2021/cuda/include -L/cineca/prod/opt/compilers/hpc-sdk/2021/binary/Linux_ppc64le/2021/cuda/lib64

LIB = -lnvToolsExt

NAME = laplace2d_kernels_data_optimized

OBJS = laplace2d.o nvtx.o

all:$(OBJS)
	$(NVCC) $(NVCCFLAGS) $(NVCCFLAGS2) $(LIB) $(OBJS) -o $(NAME)

%.o:%.c
	$(NVCC) $(NVCCFLAGS) $(NVCCFLAGS2) -c $< $(NVCCFLAGS)

clean:
	rm -r $(OBJS) *.out
