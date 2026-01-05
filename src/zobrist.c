//
// Created by ernad on 1/4/26.
//

#include "zobrist.h"
#include <stdlib.h>

static U64 zobrist_pieces[PIECE_TYPES][2][64];
static U64 zobrist_castle[16];
static U64 zobrist_side;

// Helper function to generate a random U64
static U64 random_uint64()
{
    U64 random = 0;
    for (int i = 0; i < 4; i++)
    {
        random = (random << 16) | (rand() & 0xFFFF);
    }
    return random;
}

void zobrist_init()
{
    for (int piece = 0; piece < PIECE_TYPES; piece++)
    {
        for (int side = 0; side < 2; side++)
        {
            for (int sq = 0; sq < 64; sq++)
            {
                zobrist_pieces[piece][side][sq] = random_uint64();
            }
        }
    }
    for (int i = 0; i < 16; i++)
    {
        zobrist_castle[i] = random_uint64();
    }
    zobrist_side = random_uint64();
}

U64 compute_zobrist(const Board *board)
{
    U64 key = 0;

    for (int side = 0; side < 2; side++)
    {
        for (int piece = 0; piece < PIECE_TYPES; piece++)
        {
            U64 bb = board->bitboard[piece][side];
            while (bb)
            {
                int square = __builtin_ctzll(bb);
                key ^= zobrist_pieces[piece][side][square];
                bb &= bb - 1;   //Clears the LSB
            }
        }
    }
    key ^= zobrist_castle[board->castleRights & 0x0F];

    if (board->active == BLACK) {
        key ^= zobrist_side;
    }
    return key;
}