//
// Created by ernad on 1/2/26.
//

#ifndef ACC_ENGINE_MOVE_H
#define ACC_ENGINE_MOVE_H
#include "board.h"

enum {KING_CASTLE = 1, QUEEN_CASTLE = 2, PROMOTION = 4, EN_PASSANT = 8};

//TODO cache zobrist key to move struct for undo function
typedef struct
{
    unsigned int sourceFile : 3;
    unsigned int sourceRank : 3;
    unsigned int targetFile : 3;
    unsigned int targetRank : 3;
    unsigned int piece      : 3;    //Denotes piece to move using piece enum defined in board.h
    unsigned int captured   : 3;
    unsigned int flags      : 4;    //Flags to denote special moves (such as castling)

    unsigned int halfmoveClock;
    unsigned int castleRights;
    U64 zobristKey;
} Move;

Move create_move(unsigned int sourceFile, unsigned int sourceRank, unsigned int targetFile, unsigned int targetRank,
                 unsigned int piece, unsigned int flags);

void perform_move(Board *board, Move *move);

void undo_move(Board *board, const Move *move);

void remove_piece(Board *board, const int piece, const int color, const int file, const int rank);

void add_piece(Board *board, const int piece, const int color, const int file, const int rank);

#endif //ACC_ENGINE_MOVE_H