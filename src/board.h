//
// Created by ernad on 11/4/25.
//

#ifndef ACC_ENGINE_BOARD_H
#define ACC_ENGINE_BOARD_H

#include <stdint.h>
#include "defs.h"

#define INIT_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

/* TODO
 * move history struct
 * undo move function
 */

enum {WHITE, BLACK, NONE};                                  // side enum
enum {fA, fB, fC, fD, fE, fF, fG, fH, fNONE};                      // files enum
enum {r1, r2, r3, r4, r5, r6, r7, r8, rNONE};                      // ranks enum
enum {wP, wK, wB, wR, wQ, bP, bK, bB, bR, bQ,};             // pieces enum
enum {wKCastle = 1, wQCastle = 2, bKCastle = 4, bQCastle = 8};  // castle rights enum

typedef struct
{
    // bitboards
    U64 pawns[3];                   // [0] == white, [1] == black, [2] == both
    U64 knights[3];
    U64 bishops[3];
    U64 rooks[3];
    U64 queens[3];
    U64 kings[3];

    // auxiliary bitboards
    U64 occupied[3];
    U64 empty[3];

    U8 castleRights;
    U8 active;                      // side to move
    U64 moveCount;                  // full-move count
    U8 fiftyMove;                   // half-move clock
    U8 material[3];
} Board;

Board init_Board();

void print_board(Board board);

#endif //ACC_ENGINE_BOARD_H