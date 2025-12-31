//
// Created by ernad on 12/31/25.
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/bitboard.h"
#include "../src/board.h"
#include "../src/fen.h"

void test_fen()
{
    //======================================BOARD-TO-FEN TESTS===========================================
    Board board = init_Board();

    char* fenString = board_to_fen(&board);
    printf("Fen String for INIT board:%s\n", fenString);
    char* expected = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    assert(strcmp(fenString, expected) == 0);

    clear_bit(&board.pawns[WHITE], fA, r2);
    set_bit(&board.pawns[WHITE], fA, r3);
    clear_bit(&board.pawns[NONE], fA, r2);
    set_bit(&board.pawns[NONE], fA, r3);
    clear_bit(&board.occupied[NONE], fA, r2);
    set_bit(&board.occupied[NONE], fA, r3);
    clear_bit(&board.occupied[WHITE], fA, r2);
    set_bit(&board.occupied[WHITE], fA, r3);

    board.active = BLACK;
    board.castleRights = 0;

    fenString = board_to_fen(&board);
    printf("Fen String for a2a3 board:%s\n", fenString);
    expected = "rnbqkbnr/pppppppp/8/8/8/P7/1PPPPPPP/RNBQKBNR b - - 0 1";
    assert(strcmp(fenString, expected) == 0);

    free(fenString);
}
