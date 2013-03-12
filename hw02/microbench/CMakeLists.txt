cmake_minimum_required(VERSION 2.8)

######### Project Setup
project(microbench)

ADD_DEFINITIONS(
        -O3
        -m64
        -march=corei7-avx
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
