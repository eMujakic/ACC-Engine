//
// Created by ernad on 11/4/25.
//

#include "board.h"

#define WHITE_PAWN_INIT 0xFF00ULL
#define BLACK_PAWN_INIT 0x00FF000000000000ULL

#define WHITE_ROOK_INIT 0X81ULL
#define BLACK_ROOK_INIT 0X8100000000000000ULL

#define WHITE_KNIGHT_INIT 0X42ULL
#define BLACK_KNIGHT_INIT 0X4200000000000000ULL

#define WHITE_BISHOP_INIT 0X24ULL
#define BLACK_BISHOP_INIT 0X2400000000000000ULL

#define WHITE_QUEEN_INIT 0x10ULL
#define BLACK_QUEEN_INIT 0x1000000000000000ULL

#define WHITE_KING_INIT 0x08ULL
#define BLACK_KING_INIT 0x0800000000000000ULL

Board init_Board(){
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

    board.empty[WHITE] = ~board.occupied[WHITE];
    board.empty[BLACK] = ~board.occupied[BLACK];
    board.empty[NONE] = board.empty[WHITE] & board.empty[BLACK];

    return board;
}
