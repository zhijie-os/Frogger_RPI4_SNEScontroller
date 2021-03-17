cmake_minimum_required(VERSION 3.13)
project(proj2 C)

set(CMAKE_C_STANDARD 99)

add_executable(proj2 Game.c
        constdef.h
        FrameBuffer.h
        FrameBuffer.c
        FrogFunction.h
        FrogFunction.c
        Images.h
        Images.c
        MapFunction.h
        MapFunction.c
        SNES.h
        SNES.c
        structdef.h
        )