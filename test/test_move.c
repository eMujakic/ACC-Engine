//
// Created by ernad on 1/2/26.
//

#include <assert.h>
#include <stdio.h>

#include "../src/board.h"
#include "../src/move.h"
#include "../src/bitboard.h"
#include "../src/zobrist.h"

void test_move() {
    Board board;
    init_board(&board);
    U64 initialKey = board.zobristKey;

    // Test 1: Pawn double push (e2e4)
    Move dblPawn = create_move(fE, r2, fE, r4, PAWN, 0);
    perform_move(&board, &dblPawn);
    assert(board.active == BLACK);
    assert(peek_bit(&board.bitboard[PAWN][WHITE], fE, r4) == 1);
    assert(peek_bit(&board.bitboard[PAWN][WHITE], fE, r2) == 0);
    assert(board.halfmoveClock == 0);
    undo_move(&board, &dblPawn);
    assert(board.zobristKey == initialKey);

    // Test 2: Capture with promotion
    clear_board(&board);
    add_piece(&board, PAWN, WHITE, fA, r7);
    add_piece(&board, KNIGHT, BLACK, fB, r8);
    board.zobristKey = compute_zobrist(&board);
    U64 captureKey = board.zobristKey;
    print_board(&board);

    Move capturePromo = create_move(fA, r7, fB, r8, PAWN, PROMOTION);
    perform_move(&board, &capturePromo);
    print_board(&board);
    assert(peek_bit(&board.bitboard[QUEEN][WHITE], fB, r8) == 1);
    assert(board.material[BLACK] == 0);
    undo_move(&board, &capturePromo);
    assert(board.zobristKey == captureKey);
    assert(peek_bit(&board.bitboard[PAWN][WHITE], fA, r7) == 1);
    assert(peek_bit(&board.bitboard[KNIGHT][BLACK], fB, r8) == 1);

    // Test 3: Black queenside castle
    clear_board(&board);
    add_piece(&board, KING, BLACK, fE, r8);
    add_piece(&board, ROOK, BLACK, fA, r8);
    board.castleRights = bQCastle;
    board.active = BLACK;
    board.zobristKey = compute_zobrist(&board);
    U64 blackCastleKey = board.zobristKey;

    Move qCastle = create_move(fE, r8, fC, r8, KING, QUEEN_CASTLE);
    perform_move(&board, &qCastle);
    assert(peek_bit(&board.bitboard[KING][BLACK], fC, r8) == 1);
    assert(peek_bit(&board.bitboard[ROOK][BLACK], fD, r8) == 1);
    assert(board.castleRights == 0);
    undo_move(&board, &qCastle);
    assert(board.zobristKey == blackCastleKey);
    assert(peek_bit(&board.bitboard[KING][BLACK], fE, r8) == 1);
    assert(peek_bit(&board.bitboard[ROOK][BLACK], fA, r8) == 1);

    // Test 4: En passant capture
    clear_board(&board);
    add_piece(&board, PAWN, WHITE, fD, r5);
    add_piece(&board, PAWN, BLACK, fE, r7);
    board.active = BLACK;

    // Test 5: Halfmove clock reset
    clear_board(&board);
    add_piece(&board, KNIGHT, WHITE, fB, r1);
    add_piece(&board, PAWN, BLACK, fC, r3);
    board.halfmoveClock = 10;
    board.zobristKey = compute_zobrist(&board);
    U64 halfmoveKey = board.zobristKey;

    Move capture = create_move(fB, r1, fC, r3, KNIGHT, 0);
    perform_move(&board, &capture);
    assert(board.halfmoveClock == 0);
    undo_move(&board, &capture);
    assert(board.zobristKey == halfmoveKey);
    assert(board.halfmoveClock == 10);

    // Test 6: King move removes castling rights
    clear_board(&board);
    add_piece(&board, KING, WHITE, fE, r1);
    add_piece(&board, ROOK, WHITE, fA, r1);
    board.castleRights = wKCastle | wQCastle;
    board.zobristKey = compute_zobrist(&board);
    U64 kingMoveKey = board.zobristKey;

    Move kingMove = create_move(fE, r1, fE, r2, KING, 0);
    perform_move(&board, &kingMove);
    assert(board.castleRights == 0);
    undo_move(&board, &kingMove);
    assert(board.zobristKey == kingMoveKey);
    assert(board.castleRights == (wKCastle | wQCastle));

}