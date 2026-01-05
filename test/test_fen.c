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
#include "../src/move.h"

void test_fen()
{
    //======================================BOARD-TO-FEN TESTS===========================================
    Board board;
    init_board(&board);

    // Test Case 1: Init Board
    char* fenString = board_to_fen(&board);
    printf("Fen String for INIT board:%s", fenString);
    char* expected = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    assert(strcmp(fenString, expected) == 0);
    free(fenString);
    print_board(&board);
    printf("\n");

    // Test Case 2: Move a2 to a3 (black to move, no castling rights)

    Move move = create_move(fA, r2, fA, r3, PAWN, 0);
    perform_move(&board, &move);

    fenString = board_to_fen(&board);
    printf("Fen String for a2a3 board:%s\n", fenString);
    expected = "rnbqkbnr/pppppppp/8/8/8/P7/1PPPPPPP/RNBQKBNR b KQkq - 0 1";
    assert(strcmp(fenString, expected) == 0);
    free(fenString);
    print_board(&board);
    printf("\n");

    // Test Case 3: Almost empty board (only kings and pawns)
    clear_board(&board);
    add_piece(&board, KING, BLACK, fE, r8);
    add_piece(&board, KING, WHITE, fE, r1);

    add_piece(&board, PAWN, BLACK, fA, r7);
    add_piece(&board, PAWN, WHITE, fA, r2);

    board.active = WHITE;
    board.castleRights = wQCastle | bKCastle;
    board.halfmoveClock = 0;
    board.moveCount = 5;

    fenString = board_to_fen(&board);
    printf("Fen String minimal board:%s", fenString);
    expected = "4k3/p7/8/8/8/8/P7/4K3 w Qk - 0 5";
    assert(strcmp(fenString, expected) == 0);
    free(fenString);
    print_board(&board);
    //==================================================================================================
}