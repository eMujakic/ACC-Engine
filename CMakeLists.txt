cmake_minimum_required(VERSION 4.0)
project(ACC_Engine C)

set(CMAKE_C_STANDARD 11)

add_executable(ACC_Engine
        src/main.c
        src/board.c
        src/board.h
        src/bitboard.c
        src/bitboard.h
        src/cli.c
        src/defs.h
        src/fen.h
        src/fen.c
        test/test_bitboard.c
        test/test_runner.c
        test/test.h
        test/test_fen.c
)
