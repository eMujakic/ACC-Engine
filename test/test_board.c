//
// Created by ernad on 1/2/26.
//

#include <assert.h>
#include <stdio.h>
#include "../src/board.h"

void test_board()
{
    //======================================INIT_BOARD TESTS======================================
    Board board;
    init_board(&board);
    assert(board.castleRights == (wKCastle | wQCastle | bKCastle | bQCastle));
    assert(board.active == WHITE);
    assert(board.halfmoveClock == 0);
    assert(board.moveCount == 1);
    assert(get_piece_at(&board, fA, r1) == ROOK);
    assert(get_piece_at(&board, fB, r1) == KNIGHT);
    assert(get_piece_at(&board, fC, r1) == BISHOP);
    assert(get_piece_at(&board, fD, r1) == QUEEN);
    assert(get_piece_at(&board, fE, r1) == KING);
    assert(get_piece_at(&board, fA, r5) == NO_PIECE);
    printf("Init Board:");
    print_board(&board);
    printf("\n");

    //======================================RESET_BOARD TESTS======================================
    clear_board(&board);
    assert(board.castleRights == 0);
    assert(board.active == (WHITE));
    assert(board.halfmoveClock == 0);
    assert(board.moveCount == 1);
    printf("Reset Board:");
    print_board(&board);
}
