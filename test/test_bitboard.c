//
// Created by ernad on 12/29/25.
//

#include <assert.h>
#include "../src/bitboard.h"
#include "../src/board.h"

void test_bitboard(){
    U64 bitboard = 0;

    // ========================== GET, SET, CLEAR, & PEEK TESTS ====================================================
    set_bit(&bitboard, fA, r1);
    assert(bitboard == 0x80ULL);
    assert(peek_bit(&bitboard, fA, r1) == 1);
    assert(peek_bit(&bitboard, fB, r1) == 0);
    print_bitboard(&bitboard);

    set_bit(&bitboard, fA, r2);
    assert(bitboard == 0x8080ULL);
    assert(peek_bit(&bitboard, fA, r2) == 1);
    assert(peek_bit(&bitboard, fA, r3) == 0);
    assert(peek_bit(&bitboard, fA, r1) == 1);
    print_bitboard(&bitboard);

    set_bit(&bitboard, fB, r1);
    assert(bitboard == 0x80C0ULL);
    assert(peek_bit(&bitboard, fB, r1) == 1);
    print_bitboard(&bitboard);

    clear_bit(&bitboard, fB, r1);
    assert(bitboard == 0x8080ULL);
    assert(peek_bit(&bitboard, fB, r1) == 0);
    print_bitboard(&bitboard);

    clear_bit(&bitboard, fA, r2);
    assert(bitboard == 0x80ULL);
    assert(peek_bit(&bitboard, fA, r2) == 0);
    print_bitboard(&bitboard);

    clear_bit(&bitboard, fA, r1);
    assert(bitboard == 0);
    print_bitboard(&bitboard);
}