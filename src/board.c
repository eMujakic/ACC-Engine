//
// Created by ernad on 11/4/25.
//

#include "board.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "bitboard.h"
#include "fen.h"
#include "zobrist.h"

//Bitboard values for the initial position of each piece type
#define WHITE_PAWN_INIT 0xFF00ULL
#define BLACK_PAWN_INIT 0x00FF000000000000ULL

#define WHITE_ROOK_INIT 0x81ULL
#define BLACK_ROOK_INIT 0x8100000000000000ULL

#define WHITE_KNIGHT_INIT 0x42ULL
#define BLACK_KNIGHT_INIT 0x4200000000000000ULL

#define WHITE_BISHOP_INIT 0x24ULL
#define BLACK_BISHOP_INIT 0x2400000000000000ULL

#define WHITE_QUEEN_INIT 0x10ULL
#define BLACK_QUEEN_INIT 0x1000000000000000ULL

#define WHITE_KING_INIT 0x08ULL
#define BLACK_KING_INIT 0x0800000000000000ULL

void init_board(Board *board){     //Initializes board to starting position

    board->castleRights = wKCastle | wQCastle | bKCastle | bQCastle;
    board->active = WHITE;
    board->halfmoveClock = 0;
    board->moveCount = 1;

    board->bitboard[PAWN][WHITE] = WHITE_PAWN_INIT;
    board->bitboard[PAWN][BLACK] = BLACK_PAWN_INIT;
    board->bitboard[PAWN][BOTH] = board->bitboard[PAWN][WHITE] | board->bitboard[PAWN][BLACK];

    board->bitboard[ROOK][WHITE] = WHITE_ROOK_INIT;
    board->bitboard[ROOK][BLACK] = BLACK_ROOK_INIT;
    board->bitboard[ROOK][BOTH] = board->bitboard[ROOK][WHITE] | board->bitboard[ROOK][BLACK];

    board->bitboard[KNIGHT][WHITE] = WHITE_KNIGHT_INIT;
    board->bitboard[KNIGHT][BLACK] = BLACK_KNIGHT_INIT;
    board->bitboard[KNIGHT][BOTH] = board->bitboard[KNIGHT][WHITE] | board->bitboard[KNIGHT][BLACK];

    board->bitboard[BISHOP][WHITE] = WHITE_BISHOP_INIT;
    board->bitboard[BISHOP][BLACK] = BLACK_BISHOP_INIT;
    board->bitboard[BISHOP][BOTH] = board->bitboard[BISHOP][WHITE] | board->bitboard[BISHOP][BLACK];

    board->bitboard[QUEEN][WHITE] = WHITE_QUEEN_INIT;
    board->bitboard[QUEEN][BLACK] = BLACK_QUEEN_INIT;
    board->bitboard[QUEEN][BOTH] = board->bitboard[QUEEN][WHITE] | board->bitboard[QUEEN][BLACK];

    board->bitboard[KING][WHITE] = WHITE_KING_INIT;
    board->bitboard[KING][BLACK] = BLACK_KING_INIT;
    board->bitboard[KING][BOTH] = board->bitboard[KING][WHITE] | board->bitboard[KING][BLACK];

    board->occupied[WHITE] = board->bitboard[PAWN][WHITE] | board->bitboard[ROOK][WHITE] |board->bitboard[KNIGHT][WHITE] | board->bitboard[BISHOP][WHITE] | board->bitboard[QUEEN][WHITE] | board->bitboard[KING][WHITE];
    board->occupied[BLACK] = board->bitboard[PAWN][BLACK] | board->bitboard[ROOK][BLACK] |board->bitboard[KNIGHT][BLACK] | board->bitboard[BISHOP][BLACK] | board->bitboard[QUEEN][BLACK] | board->bitboard[KING][BLACK];
    board->occupied[BOTH] = board->occupied[WHITE] | board->occupied[BLACK];

    board->empty = ~(board->occupied[WHITE] | board->occupied[BLACK]);
    board->material[WHITE] = INIT_MATERIAL; board->material[BLACK] = INIT_MATERIAL; board->material[BOTH] = INIT_MATERIAL * 2;
    board->zobristKey = compute_zobrist(board); //TODO cache value to optimize calculation
}

void print_board(const Board* board)    //Prints board to command-line
{
    for (int rank = r8; rank >= r1; rank--)
    {
        printf("\n%d |  ", rank + 1);   //Prints rank numbers

        for (int file = fA; file < fNONE; file++)
        {
            if (peek_bit(&board->occupied[BOTH], file, rank))
            {
                char piece = get_piece_at(board, file, rank);
                if      (piece == PAWN)     piece = 'p';
                else if (piece == ROOK)     piece = 'r';
                else if (piece == KNIGHT)   piece = 'n';
                else if (piece == BISHOP)   piece = 'b';
                else if (piece == QUEEN)    piece = 'q';
                else if (piece == KING)     piece = 'k';

                if (peek_bit(&board->occupied[WHITE], file, rank)) piece = toupper(piece);

                printf(" %c  ",piece);
            }
            else printf(" .  ");
        }
    }
    printf("\n  ----------------------------------\n");
    printf("      a   b   c   d   e   f   g   h\n");    //Prints file letters
}

void clear_board(Board *board)
{
    board->bitboard[PAWN][WHITE] = 0ULL; board->bitboard[PAWN][BLACK] = 0ULL; board->bitboard[PAWN][BOTH] = 0ULL;
    board->bitboard[ROOK][WHITE] = 0ULL; board->bitboard[ROOK][BLACK] = 0ULL; board->bitboard[ROOK][BOTH] = 0ULL;
    board->bitboard[KNIGHT][WHITE] = 0ULL; board->bitboard[KNIGHT][BLACK] = 0ULL; board->bitboard[KNIGHT][BOTH] = 0ULL;
    board->bitboard[BISHOP][WHITE] = 0ULL; board->bitboard[BISHOP][BLACK] = 0ULL; board->bitboard[BISHOP][BOTH] = 0ULL;
    board->bitboard[QUEEN][WHITE] = 0ULL; board->bitboard[QUEEN][BLACK] = 0ULL; board->bitboard[QUEEN][BOTH] = 0ULL;
    board->bitboard[KING][WHITE] = 0ULL; board->bitboard[KING][BLACK] = 0ULL; board->bitboard[KING][BOTH] = 0ULL;

    board->occupied[WHITE] = 0ULL; board->occupied[BLACK] = 0ULL; board->occupied[BOTH] = 0ULL;
    board->material[WHITE] = 0; board->material[BLACK] = 0; board->material[BOTH] = 0;
    board->empty = 0xFFFFFFFFFFFFFFFFULL;

    board->castleRights = 0;
    board->active = WHITE;
    board->halfmoveClock = 0;
    board->moveCount = 1;
    board->zobristKey = compute_zobrist(board); //TODO cache value to optimize calculation
}

int get_piece_at(const Board *board, const int file, const int rank)
{
    if (!peek_bit(&board->occupied[BOTH], file, rank)) return NO_PIECE;

    int side = peek_bit(&board->occupied[BLACK], file, rank);

    if (peek_bit(&board->bitboard[PAWN][side], file, rank)) return PAWN;
    if (peek_bit(&board->bitboard[ROOK][side], file, rank)) return ROOK;
    if (peek_bit(&board->bitboard[KNIGHT][side], file, rank)) return KNIGHT;
    if (peek_bit(&board->bitboard[BISHOP][side], file, rank)) return BISHOP;
    if (peek_bit(&board->bitboard[QUEEN][side], file, rank)) return QUEEN;
    if (peek_bit(&board->bitboard[KING][side], file, rank)) return KING;

    return NO_PIECE;
}