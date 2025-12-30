//
// Created by ernad on 12/29/25.
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "bitboard.h"
#include "board.h"

Board parse_fen(const char* fen)
{
    Board board;

    for (int i = 0; fen[i] != '\0'; i++){
        int rank = r8;
        int file = fA;

        if (fen[i] == '/')
        {
            rank--;
            file = fA;
            continue;
        }
        else if (isdigit(fen[i]))
        {
            for (int file = (int) fen[i]; file > 0; file--)
            {
                for (int i = 0; i < 3; i++)
                clear_bit(&board.pawns[i], file, rank);
                clear_bit(&board.knights[i], file, rank);
                clear_bit(&board.bishops[i], file, rank);
                clear_bit(&board.rooks[i], file, rank);
                clear_bit(&board.queens[i], file, rank);
                clear_bit(&board.kings[i], file, rank);
                clear_bit(&board.occupied[i], file, rank);
                clear_bit(&board.empty[i], file, rank);
            }
        }
        else if (isalpha(fen[i]))
        {
            int side = isupper(fen[i]) ? 0 : 1;

            switch (tolower(fen[i]))
            {
            case 'p':
                set_bit(&board.pawns[side], file, rank);
                set_bit(&board.pawns[2], file, rank);
                break;
            case 'r':
                set_bit(&board.rooks[side], file, rank);
                set_bit(&board.rooks[2], file, rank);
                break;
            case 'n':
                set_bit(&board.knights[side], file, rank);
                set_bit(&board.knights[2], file, rank);
                break;
            case 'b':
                set_bit(&board.bishops[side], file, rank);
                set_bit(&board.bishops[2], file, rank);
                break;
            case 'q':
                set_bit(&board.queens[side], file, rank);
                set_bit(&board.queens[2], file, rank);
                break;
            case 'k':
                set_bit(&board.kings[side], file, rank);
                set_bit(&board.kings[2], file, rank);
                break;
            default:
                fprintf(stderr, "Unrecognized fen\n");
                exit(1);
            }
        }
        file++;
    }
}