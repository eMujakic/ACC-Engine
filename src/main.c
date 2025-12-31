//
// Created by ernad on 8/29/25.
//

#include <stdio.h>
#include "defs.h"
#include <assert.h>
#include "bitboard.h"
#include "board.h"
#include "../test/test.h"

/* TODO:
 * board representation
 * lookup table translation init
 * board history struct
 * piecelists
 * UCI protocol
 * FEN parsing and generation
 * zobrist key
 * perft??
 * linkedlist impl
 * test env
 */

#define DEBUG

int main()
{

#ifdef  DEBUG
    run_tests();
#endif

    return 0;
}
