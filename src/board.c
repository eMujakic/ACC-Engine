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

Board init_Board(){     //Initializes board to starting position
    Board board;

    board.castleRights = wKCastle | wQCastle | bKCastle | bQCastle;
    board.active = WHITE;
    board.fiftyMove = 0;
    board.moveCount = 1;

    board.pawns[WHITE] = WHITE_PAWN_INIT;
    board.pawns[BLACK] = BLACK_PAWN_INIT;
    board.pawns[NONE] = board.pawns[WHITE] | board.pawns[BLACK];

    board.rooks[WHITE] = WHITE_ROOK_INIT;
    board.rooks[BLACK] = BLACK_ROOK_INIT;
    board.rooks[NONE] = board.rooks[WHITE] | board.rooks[BLACK];

    board.knights[WHITE] = WHITE_KNIGHT_INIT;
    board.knights[BLACK] = BLACK_KNIGHT_INIT;
    board.knights[NONE] = board.knights[WHITE] | board.knights[BLACK];

    board.bishops[WHITE] = WHITE_BISHOP_INIT;
    board.bishops[BLACK] = BLACK_BISHOP_INIT;
    board.bishops[NONE] = board.bishops[WHITE] | board.bishops[BLACK];

    board.queens[WHITE] = WHITE_QUEEN_INIT;
    board.queens[BLACK] = BLACK_QUEEN_INIT;
    board.queens[NONE] = board.queens[WHITE] | board.queens[BLACK];

    board.kings[WHITE] = WHITE_KING_INIT;
    board.kings[BLACK] = BLACK_KING_INIT;
    board.kings[NONE] = board.kings[WHITE] | board.kings[BLACK];

    board.occupied[WHITE] = board.pawns[WHITE] | board.rooks[WHITE] |board.knights[WHITE] | board.bishops[WHITE] | board.queens[WHITE] | board.kings[WHITE];
    board.occupied[BLACK] = board.pawns[BLACK] | board.rooks[BLACK] | board.knights[BLACK] | board.bishops[BLACK] | board.queens[BLACK] | board.kings[BLACK];
    board.occupied[NONE] = board.occupied[WHITE] | board.occupied[BLACK];

    board.empty = ~(board.occupied[WHITE] | board.occupied[BLACK]);

    return board;
}

void print_board(const Board* board)
{
    char* fenString = board_to_fen(board);
    int index = 0;

    for (int rank = r8; rank >= r1; rank--)
    {
        printf("\n%d |  ", rank + 1);

        for (int file = fA; file <= fNONE;)
        {
            if (fenString[index] == '\0') break;

            if (fenString[index] == '/')
            {
                index++;
                break;
            }
            if (isdigit(fenString[index]))
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
                printf(" %c  ", fenString[index++]);
                file++;
            }
        }
    }
    printf("\n  ----------------------------------\n");
    printf("      a   b   c   d   e   f   g   h\n");
}
