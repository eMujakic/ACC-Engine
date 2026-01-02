//
// Created by ernad on 1/2/26.
//

#include <stdio.h>
#include "../src/board.h"

void test_board()
{
    //======================================INIT_BOARD TESTS======================================
    Board board;
    init_board(&board);
    printf("Init Board:");
    print_board(&board);
    printf("\n");

    //======================================RESET_BOARD TESTS======================================
    reset_board(&board);
    printf("Reset Board:");
    print_board(&board);
}
