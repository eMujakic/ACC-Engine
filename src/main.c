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
 * Move Representation
 * (generated) Move List Management
 * Move Execution & Undo
 * Attack and Check Detection (Bitboard Raycasting)
 * Move-To-String Function
 * UCI protocol
 * FEN parsing
 * zobrist key
 * perft??
 */

#define DEBUG

int main()
{

#ifdef  DEBUG
    run_tests();
#endif

    return 0;
}
