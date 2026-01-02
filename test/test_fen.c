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

    // Test Case 1: Init Board
    char* fenString = board_to_fen(&board);
    printf("Fen String for INIT board:%s", fenString);
    char* expected = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    assert(strcmp(fenString, expected) == 0);
    free(fenString);
    print_board(&board);
    printf("\n");

    // Test Case 2: Move a2 to a3 (black to move, no castling rights)
    clear_bit(&board.pawns[WHITE], fA, r2);
    set_bit(&board.pawns[WHITE], fA, r3);
    clear_bit(&board.pawns[NONE], fA, r2);
    set_bit(&board.pawns[NONE], fA, r3);
    clear_bit(&board.occupied[WHITE], fA, r2);
    set_bit(&board.occupied[WHITE], fA, r3);
    clear_bit(&board.occupied[NONE], fA, r2);
    set_bit(&board.occupied[NONE], fA, r3);

    board.active = BLACK;
    board.castleRights = 0;

    fenString = board_to_fen(&board);
    printf("Fen String for a2a3 board:%s\n", fenString);
    expected = "rnbqkbnr/pppppppp/8/8/8/P7/1PPPPPPP/RNBQKBNR b - - 0 1";
    assert(strcmp(fenString, expected) == 0);
    free(fenString);
    print_board(&board);
    printf("\n");

    // Test Case 3: Almost empty board (only kings and pawns)
    board = init_Board();
    // Clear all pieces except kings and pawns
    board.knights[WHITE] = 0; board.knights[BLACK] = 0; board.knights[NONE] = 0;
    board.bishops[WHITE] = 0; board.bishops[BLACK] = 0; board.bishops[NONE] = 0;
    board.rooks[WHITE] = 0;   board.rooks[BLACK] = 0; board.rooks[NONE] = 0;
    board.queens[WHITE] = 0;  board.queens[BLACK] = 0; board.queens[NONE] = 0;
    // Update occupied boards
    board.occupied[WHITE] = board.pawns[WHITE] | board.kings[WHITE];
    board.occupied[BLACK] = board.pawns[BLACK] | board.kings[BLACK];
    board.occupied[NONE] = board.occupied[WHITE] | board.occupied[BLACK];

    board.active = WHITE;
    board.castleRights = wQCastle | bKCastle;
    board.fiftyMove = 0;
    board.moveCount = 5;

    fenString = board_to_fen(&board);
    printf("Fen String minimal board:%s", fenString);
    expected = "4k3/pppppppp/8/8/8/8/PPPPPPPP/4K3 w Qk - 0 5";
    assert(strcmp(fenString, expected) == 0);
    free(fenString);
    print_board(&board);
    //==================================================================================================
}