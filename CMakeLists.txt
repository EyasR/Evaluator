cmake_minimum_required(VERSION 3.13)
project(Asg6_EyasRashid)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Asg6_EyasRashid
        driver.cpp
        evaluator.cpp.h
        evaluator.h
        token.h
        tokenizer.cpp.h
        tokenizer.h)
