//
// Created by ernad on 11/4/25.
//

#include "board.h"

#include <ctype.h>
#include <stdio.h>

#include "fen.h"

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

#define INIT_MATERIAL 39

void init_board(Board *board){     //Initializes board to starting position

    board->castleRights = wKCastle | wQCastle | bKCastle | bQCastle;
    board->active = WHITE;
    board->fiftyMove = 0;
    board->moveCount = 1;

    board->pawns[WHITE] = WHITE_PAWN_INIT;
    board->pawns[BLACK] = BLACK_PAWN_INIT;
    board->pawns[NONE] = board->pawns[WHITE] | board->pawns[BLACK];

    board->rooks[WHITE] = WHITE_ROOK_INIT;
    board->rooks[BLACK] = BLACK_ROOK_INIT;
    board->rooks[NONE] = board->rooks[WHITE] | board->rooks[BLACK];

    board->knights[WHITE] = WHITE_KNIGHT_INIT;
    board->knights[BLACK] = BLACK_KNIGHT_INIT;
    board->knights[NONE] = board->knights[WHITE] | board->knights[BLACK];

    board->bishops[WHITE] = WHITE_BISHOP_INIT;
    board->bishops[BLACK] = BLACK_BISHOP_INIT;
    board->bishops[NONE] = board->bishops[WHITE] | board->bishops[BLACK];

    board->queens[WHITE] = WHITE_QUEEN_INIT;
    board->queens[BLACK] = BLACK_QUEEN_INIT;
    board->queens[NONE] = board->queens[WHITE] | board->queens[BLACK];

    board->kings[WHITE] = WHITE_KING_INIT;
    board->kings[BLACK] = BLACK_KING_INIT;
    board->kings[NONE] = board->kings[WHITE] | board->kings[BLACK];

    board->occupied[WHITE] = board->pawns[WHITE] | board->rooks[WHITE] |board->knights[WHITE] | board->bishops[WHITE] | board->queens[WHITE] | board->kings[WHITE];
    board->occupied[BLACK] = board->pawns[BLACK] | board->rooks[BLACK] | board->knights[BLACK] | board->bishops[BLACK] | board->queens[BLACK] | board->kings[BLACK];
    board->occupied[NONE] = board->occupied[WHITE] | board->occupied[BLACK];

    board->empty = ~(board->occupied[WHITE] | board->occupied[BLACK]);
    board->material[WHITE] = INIT_MATERIAL; board->material[BLACK] = INIT_MATERIAL; board->material[NONE] = INIT_MATERIAL * 2;
}

void print_board(const Board* board)    //Prints board to command-line
{
    char* fenString = board_to_fen(board);
    int index = 0;  //Current index in fenString

    for (int rank = r8; rank >= r1; rank--)
    {
        printf("\n%d |  ", rank + 1);   //Prints rank numbers

        for (int file = fA; file <= fNONE;)
        {
            if (fenString[index] == '/')    //Moves on to next rank
            {
                index++;
                break;
            }
            if (isdigit(fenString[index]))  //Prints corresponding number of .'s for empty squares
            {
                int num = fenString[index] - '0';
                for (int i = 0; i < num; i++)
                {
                    printf(" .  ");
                    file++;
                }
                index++;
            }
            else
            {
                printf(" %c  ", fenString[index++]);    //Prints fenString representation of piece
                file++;
            }
        }
    }
    printf("\n  ----------------------------------\n");
    printf("      a   b   c   d   e   f   g   h\n");    //Prints file letters
}

void reset_board(Board *board)
{
    board->pawns[WHITE] = 0ULL; board->pawns[BLACK] = 0ULL; board->pawns[NONE] = 0ULL;
    board->rooks[WHITE] = 0ULL; board->rooks[BLACK] = 0ULL; board->rooks[NONE] = 0ULL;
    board->knights[WHITE] = 0ULL; board->knights[BLACK] = 0ULL; board->knights[NONE] = 0ULL;
    board->bishops[WHITE] = 0ULL; board->bishops[BLACK] = 0ULL; board->bishops[NONE] = 0ULL;
    board->queens[WHITE] = 0ULL; board->queens[BLACK] = 0ULL; board->queens[NONE] = 0ULL;
    board->kings[WHITE] = 0ULL; board->kings[BLACK] = 0ULL; board->kings[NONE] = 0ULL;

    board->occupied[WHITE] = 0ULL; board->occupied[BLACK] = 0ULL; board->occupied[NONE] = 0ULL;
    board->material[WHITE] = 0; board->material[BLACK] = 0; board->material[NONE] = 0;
    board->empty = 0xFFFFFFFFFFFFFFFFULL;

    board->castleRights = 0;
    board->active = WHITE;
    board->fiftyMove = 0;
    board->moveCount = 1;

}