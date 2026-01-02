//
// Created by ernad on 12/29/25.
//

#include "fen.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bitboard.h"
#include "board.h"

#define FEN_LENGTH 100

char* castling_rights_to_fen(U8 rights)         // Takes an 8-bit castlingRights integer, and returns the
{                                               // corresponding fen substring for castling rights
    char* stringRights = malloc(sizeof(char) * 5);
    int index = 0;

    if (!rights) stringRights[index++] = '-';
    else
    {
        if (rights & (wKCastle)) stringRights[index++] = 'K';
        if (rights & (wQCastle)) stringRights[index++] = 'Q';
        if (rights & (bKCastle)) stringRights[index++] = 'k';
        if (rights & (bQCastle)) stringRights[index++] = 'q';
    }

    stringRights[index] = '\0';
    return stringRights;    // MUST BE FREED TO AVOID MEMORY LEAKS!!
}

char* board_to_fen(const Board* board)
{
    char* fen = (char*)malloc(FEN_LENGTH * sizeof(char));

    if (fen == NULL)    // if memory allocation fails...
    {
        return NULL;
    }

    int index = 0;      // index of current position in fen

    for (int rank = r8; rank >= r1; rank--)
    {
        int emptyCount = 0;     // num of consecutive empty squares

        for (int file = fA; file < fNONE; file++)
        {
            if (peek_bit(&board->occupied[NONE], file, rank))
            {
                int side = peek_bit(&board->occupied[WHITE], file, rank) ? WHITE : BLACK;
                char piece = '0';

                if (peek_bit(&board->rooks[side], file, rank)) piece = 'R';
                else if (peek_bit(&board->knights[side], file, rank)) piece = 'N';
                else if (peek_bit(&board->bishops[side], file, rank)) piece = 'B';
                else if (peek_bit(&board->queens[side], file, rank)) piece = 'Q';
                else if (peek_bit(&board->kings[side], file, rank)) piece = 'K';
                else if (peek_bit(&board->pawns[side], file, rank)) piece = 'P';
                else
                {
                    fprintf(stderr, "Unrecognized piece\n");
                    free(fen);
                    exit(EXIT_FAILURE);
                }

                if (side == BLACK) piece = tolower(piece);

                if (emptyCount > 0)
                {
                    fen[index++] = '0' + emptyCount;
                    emptyCount = 0;
                }

                fen[index++] = piece;
            }
            else emptyCount++;
        }
        if (emptyCount > 0)
        {
            fen[index++] = '0' + emptyCount;
            emptyCount = 0;
        }
        fen[index] = '/';
        index++;
    }
    fen[index - 1] = ' ';       // replaces last '/' with a space

    fen[index++] = board->active == WHITE ? 'w' : 'b';
    fen[index++] = ' ';

    char* strCastleRights = castling_rights_to_fen(board->castleRights);
    int len = strlen(strCastleRights);
    memcpy(fen + index, strCastleRights, len);
    index += len;
    free(strCastleRights);

    strcpy(&fen[index], " - "); // en passant placeholder
    index += 3;

    index += snprintf(&fen[index], 10, "%d %lu", board->fiftyMove, board->moveCount);

    fen[index] = '\0';
    return fen;     // MUST BE FREED!!
}