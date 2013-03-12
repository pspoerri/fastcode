cmake_minimum_required(VERSION 2.8)

######### Project Setup
project(microbench)
SET(CMAKE_C_COMPILER gcc-4.7)
SET(CMAKE_CXX_COMPILER g++-4.7)
ADD_DEFINITIONS(
        -O3
        -m64
        -march=corei7-avx
        -fno-tree-vectorize
#-mfpmath=sse,387
        )

SET(SRC
        main.cpp
        microbench_cos.c
        microbench_exp.c
        microbench_log.c
        microbench_sin.c
        microbench_oneover.c
        microbench_sin.c
        microbench_squared.c
   )

add_executable(main ${SRC})
