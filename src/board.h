//
// Created by ernad on 11/4/25.
//

#ifndef ACC_ENGINE_BOARD_H
#define ACC_ENGINE_BOARD_H

#include <stdint.h>
#include "defs.h"

#define PIECE_TYPES 6
#define INIT_MATERIAL 39

#define EMPTY(board)  (~(board->occupied[WHITE] | board->occupied[BLACK]))

/* TODO
 * board history struct
 */

enum {WHITE, BLACK, BOTH};                                          // side enum
enum {fA, fB, fC, fD, fE, fF, fG, fH, fNONE};                       // files enum
enum {r1, r2, r3, r4, r5, r6, r7, r8, rNONE};                       // ranks enum
enum {PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING, NO_PIECE};           // pieces enum
enum {wKCastle = 1, wQCastle = 2, bKCastle = 4, bQCastle = 8};      // castle rights enum

typedef struct
{
    U64 bitboard[PIECE_TYPES][3];   // First dimension is indexed using the pieces enum
                                    // Second dimension is indexed using the side enum
    // auxiliary bitboards
    U64 occupied[3];
    U64 empty;                      //TODO remove and use macro

    U8 castleRights;
    U8 active;                      // side to move
    U64 moveCount;                  // full-move count
    U8 halfmoveClock;               // half-move clock
    U8 material[3];

    U64 zobristKey;
} Board;

void init_board(Board *board);

void print_board(const Board *board);

void clear_board(Board *board);

int get_piece_at(const Board *board, const int file, const int rank);

#endif //ACC_ENGINE_BOARD_H