//
// Created by ernad on 11/4/25.
//

#ifndef ACC_ENGINE_BITBOARD_H
#define ACC_ENGINE_BITBOARD_H
#include "defs.h"


void set_bit(U64 *bitboard, int file, int rank);

void clear_bit(U64 *bitboard, int file, int rank);

U64 peek_bit(U64 const *bitboard, int file, int rank);

void print_bitboard(U64 const *bitboard);

#endif //ACC_ENGINE_BITBOARD_H
