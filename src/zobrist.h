//
// Created by ernad on 1/4/26.
//

#ifndef ACC_ENGINE_ZOBRIST_H
#define ACC_ENGINE_ZOBRIST_H
#include "board.h"

void zobrist_init();
U64 compute_zobrist(const Board* board);

#endif //ACC_ENGINE_ZOBRIST_H