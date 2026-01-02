//
// Created by ernad on 11/4/25.
//

#include "board.h"
#include <stdio.h>

/* ================================================================================
 * bitboards use big-endian representation
 * for example, in the byte:
 * 1  0  0  1  1  0  1  1
 * ^                    ^
 * a1                   h1
 * ================================================================================
 */

void set_bit(U64* bitboard, int file, int rank)
{
    if (file >= fA && file <= fH && rank >= r1 && rank <= r8)
    {
        *bitboard |= 1ULL << ((7 - file) + rank*8);
    }
}

void clear_bit(U64 *bitboard, int file, int rank)
{
    if (file >= fA && file <= fH && rank >= r1 && rank <= r8)
    {
        *bitboard &= ~(1ULL << ((7 - file) + rank*8));
    }
}

int peek_bit(const U64 *bitboard, int file, int rank)
{
    return (*bitboard & (1ULL << ((7 - file) + rank*8))) ? 1 : 0;
}

void print_bitboard(const U64 *bitboard) {
    printf("\nPrinting Bitboard 0x%llx...\n", *bitboard);

    for (int rank = r8; rank >= r1; rank--) {
        printf("%d | ", rank + 1);
        for (int file = fA; file < fNONE; file++) {
            printf(" %d  ", peek_bit(bitboard, file, rank));
        }
        printf("\n");
    }
    printf("  --------------------------------\n");
    printf("     a   b   c   d   e   f   g   h\n");
}