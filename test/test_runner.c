//
// Created by ernad on 12/29/25.
//

#include <stdio.h>

#include "test.h"

void run_tests()
{
    printf("Running Tests...\n");

    printf("========================Zobrist Tests========================\n\n");
    test_zobrist();
    printf("Zobrist Tests Completed!\n");

    printf("\n========================Bitboard Tests========================\n");
    test_bitboard();
    printf("\nBitboard Tests Completed!\n\n");

    printf("========================Fen Tests========================\n\n");
    test_fen();
    printf("\nFen Tests Completed!\n");

    printf("========================Board Tests========================\n\n");
    test_board();
    printf("\nBoard Tests Completed!\n");

    printf("========================Move Tests========================\n\n");
    test_move();
    printf("\nMove Tests Completed!\n");
}