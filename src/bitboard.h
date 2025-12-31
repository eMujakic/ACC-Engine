//
// Created by ernad on 11/4/25.
//

#ifndef ACC_ENGINE_BITBOARD_H
#define ACC_ENGINE_BITBOARD_H
#include "defs.h"


void set_bit(U64 *bitboard, int file, int rank);

void clear_bit(U64 *bitboard, int file, int rank);

U64 peek_bit(const U64 *bitboard, int file, int rank);

void print_bitboard(const U64 *bitboard);

#endif //ACC_ENGINE_BITBOARD_H
