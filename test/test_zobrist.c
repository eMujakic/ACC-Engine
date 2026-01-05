//
// Created by ernad on 1/5/26.
//

#include <assert.h>
#include <stdio.h>

#include "../src/move.h"
#include "../src/zobrist.h"

void test_zobrist()
{
    Board board;
    init_board(&board);
    int key1 = board.zobristKey;

    Move move = create_move(fA, r2, fA, r4, PAWN, 0);
    perform_move(&board, &move);

    int key2 = board.zobristKey;

    assert(key1 != key2);

    move = create_move(fB, r1, fC, r3, KNIGHT, 0);
    perform_move(&board, &move);

    int key3 = board.zobristKey;

    assert(key1 != key2 != key3);
}