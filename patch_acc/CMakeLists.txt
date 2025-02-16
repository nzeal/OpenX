# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(PatchProcessing)

# Manually set the path to the nvhpc compiler (adjust the path if needed)
set(CMAKE_C_COMPILER /leonardo/prod/spack/5.2/install/0.21/linux-rhel8-icelake/gcc-8.5.0/nvhpc-24.3-v63z4inohb4ywjeggzhlhiuvuoejr2le/Linux_x86_64/24.3/compilers/bin/nvc)
set(CMAKE_CXX_COMPILER /leonardo/prod/spack/5.2/install/0.21/linux-rhel8-icelake/gcc-8.5.0/nvhpc-24.3-v63z4inohb4ywjeggzhlhiuvuoejr2le/Linux_x86_64/24.3/compilers/bin/nvc++)

# Set the compiler flags for nvhpc - add the -acc=noautopar flag to fix linking issues
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -acc -gpu=cc80 -gpu=managed -Minfo=all -cuda")

# Specify the source file
set(SOURCE_FILE1 offloadPatches.c)
# Specify the output binary name
set(OUTPUT_BINARY1 offloadpatch)
set(SOURCE_FILE2 patch.c)
set(OUTPUT_BINARY2 patch)

# Add executable
add_executable(${OUTPUT_BINARY1} ${SOURCE_FILE1})
add_executable(${OUTPUT_BINARY2} ${SOURCE_FILE2})

# Optionally, you can set the output path for the executable
set_target_properties(${OUTPUT_BINARY1} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
set_target_properties(${OUTPUT_BINARY2} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
