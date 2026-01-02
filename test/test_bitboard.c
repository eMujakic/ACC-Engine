//
// Created by ernad on 12/29/25.
//

#include <assert.h>
#include <stdio.h>
#include "../src/bitboard.h"
#include "../src/board.h"

void test_bitboard() {
    U64 bitboard = 0;

    // ======================== GET, SET, CLEAR, & PEEK TESTS ========================

    // Test 1: Corner squares (a1, h1, a8, h8)
    set_bit(&bitboard, fA, r1);   // a1 (LSB)
    assert(bitboard == 0x0000000000000080ULL);
    set_bit(&bitboard, fH, r1);   // h1
    assert(bitboard == 0x0000000000000081ULL);
    set_bit(&bitboard, fA, r8);   // a8
    assert(bitboard == 0x8000000000000081ULL);
    set_bit(&bitboard, fH, r8);   // h8 (MSB)
    assert(bitboard == 0x8000000000000081ULL | (1ULL << 63));
    print_bitboard(&bitboard);
    clear_bit(&bitboard, fA, r1);
    clear_bit(&bitboard, fH, r1);
    clear_bit(&bitboard, fA, r8);
    clear_bit(&bitboard, fH, r8);
    assert(bitboard == 0);

    // Test 2: Multiple isolated bits
    int squares[][2] = {{fC, r2}, {fF, r6}, {fB, r7}, {fG, r1}};
    for (int i = 0; i < 4; i++) {
        set_bit(&bitboard, squares[i][0], squares[i][1]);
    }
    assert(bitboard ==
        (1ULL << (1*8+2)) |  // c2
        (1ULL << (5*8+5)) |  // f6
        (1ULL << (6*8+1)) |  // b7
        (1ULL << (0*8+6)));  // g1
    print_bitboard(&bitboard);
    bitboard = 0;

    // Test 3: Set/clear same bit repeatedly
    for (int i = 0; i < 3; i++) {
        set_bit(&bitboard, fE, r4);
        set_bit(&bitboard, fE, r4);  // Intentional duplicate
    }
    assert(peek_bit(&bitboard, fE, r4) == 1);
    for (int i = 0; i < 3; i++) {
        clear_bit(&bitboard, fE, r4);
    }
    assert(peek_bit(&bitboard, fE, r4) == 0);
    print_bitboard(&bitboard);

    // Test 4: Invalid coordinates (should be safe)
    set_bit(&bitboard, -1, 2);     // Invalid file
    set_bit(&bitboard, 8, 2);      // Invalid file
    set_bit(&bitboard, 3, -1);     // Invalid rank
    set_bit(&bitboard, 3, 8);      // Invalid rank
    assert(bitboard == 0);                  // Should remain unchanged

    // Test 5: Full-board tests
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            set_bit(&bitboard, file, rank);
            assert(peek_bit(&bitboard, file, rank) == 1);
        }
    }
    assert(bitboard == 0xFFFFFFFFFFFFFFFF);  // All bits set
    print_bitboard(&bitboard);
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            assert(peek_bit(&bitboard, file, rank) == 1);
            clear_bit(&bitboard, file, rank);
        }
    }
    assert(bitboard == 0);  // All bits cleared
}
