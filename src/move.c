//
// Created by ernad on 1/2/26.
//

#include "board.h"
#include "move.h"


#include "bitboard.h"
#include "zobrist.h"

const int material_vals[] = {1, 5, 3, 3, 9, 0}; //KING is 0-valued

Move create_move(unsigned int sourceFile, unsigned int sourceRank, unsigned int targetFile, unsigned int targetRank,
                 unsigned int piece, unsigned int flags)
{
    Move move;
    move.sourceFile = sourceFile;
    move.sourceRank = sourceRank;
    move.targetFile = targetFile;
    move.targetRank = targetRank;
    move.piece = piece;
    move.flags = flags;
    move.halfmoveClock = 0;
    move.castleRights = 0;
    move.zobristKey = 0;
    move.captured = NO_PIECE;

    return move;
}

static void update_castling_rights(Board *board, const Move *move) {
    //Remove rights if king is moved
    if (move->piece == KING) {
        board->castleRights &= ~(board->active == WHITE ? (wKCastle | wQCastle) : (bKCastle | bQCastle));
    }
    //Remove corresponding rights if rook is moved
    else if (move->piece == ROOK) {
        if (board->active == WHITE && move->sourceRank == r1) {
            if (move->sourceFile == fA) board->castleRights &= ~wQCastle;
            else if (move->sourceFile == fH) board->castleRights &= ~wKCastle;
        }
        else if (board->active == BLACK && move->sourceRank == r8) {
            if (move->sourceFile == fA) board->castleRights &= ~bQCastle;
            else if (move->sourceFile == fH) board->castleRights &= ~bKCastle;
        }
    }
}

static void perform_capture(Board *board, const Move *move)
{
    remove_piece(board, move->captured, !board->active, move->targetFile, move->targetRank);

    if (move->captured == ROOK)
    {
        if (!board->active == WHITE)
        {
            if (move->targetFile == fA)
                board->castleRights &= ~wQCastle;
            else if (move->targetFile == fH)
                board->castleRights &= ~wKCastle;
        }
        else
        {
            if (move->targetFile == fA)
                board->castleRights &= ~bQCastle;
            else if (move->targetFile == fH)
                board->castleRights &= ~bKCastle;
        }
    }
}

void remove_piece(Board *board, const int piece, const int color, const int file, const int rank)
{

    clear_bit(&board->bitboard[piece][color], file, rank);
    clear_bit(&board->bitboard[piece][BOTH], file, rank);

    clear_bit(&board->occupied[color], file, rank);
    clear_bit(&board->occupied[BOTH], file, rank);

    set_bit(&board->empty, file, rank);

    board->material[color] -= material_vals[piece];
    board->material[BOTH] -= material_vals[piece];
}

void add_piece(Board *board, const int piece, const int color, const int file, const int rank)
{

    set_bit(&board->bitboard[piece][color], file, rank);
    set_bit(&board->bitboard[piece][BOTH], file, rank);

    set_bit(&board->occupied[color], file, rank);
    set_bit(&board->occupied[BOTH], file, rank);

    clear_bit(&board->empty, file, rank);

    board->material[color] += material_vals[piece];
    board->material[BOTH] += material_vals[piece];
}

static void perform_castle(Board *board, const Move *move) //TODO ensure legality of castle & Rights???
{
    const int rank = board->active == WHITE ? r1 : r8;
    const int kingTargetFile = move->flags & KING_CASTLE ? fG: fC;
    remove_piece(board, KING, board->active, fE, rank);
    add_piece(board, KING, board->active, kingTargetFile, rank);

    const int rookSourceFile = move->flags & KING_CASTLE ? fH: fA;
    const int rookTargetFile = move->flags & KING_CASTLE ? fF: fD;
    remove_piece(board, ROOK, board->active, rookSourceFile, rank);
    add_piece(board, ROOK, board->active, rookTargetFile, rank);

    board->castleRights &= ~(board->active == WHITE ? (wKCastle | wQCastle) : (bKCastle | bQCastle));
}

static void undo_castle(Board *board, const Move *move)
{
    const int rank = board->active == WHITE ? r1 : r8;
    const int kingSourceFile = move->flags & KING_CASTLE ? fG: fC;
    remove_piece(board, KING, board->active, kingSourceFile, rank);
    add_piece(board, KING, board->active, fE, rank);

    const int rookSourceFile = move->flags & KING_CASTLE ? fF: fD;
    const int rookTargetFile = move->flags & KING_CASTLE ? fH: fA;
    remove_piece(board, ROOK, board->active, rookSourceFile, rank);
    add_piece(board, ROOK, board->active, rookTargetFile, rank);
}

void perform_move(Board *board, Move *move)
{
    move->castleRights = board->castleRights;
    move->halfmoveClock = board->halfmoveClock;

    int capture = peek_bit(&board->occupied[!board->active], move->targetFile, move->targetRank);

    if (capture)
    {
        move->captured = get_piece_at(board, move->targetFile, move->targetRank);
        perform_capture(board, move);
    }

    if (move->flags & KING_CASTLE || move->flags & QUEEN_CASTLE)
        perform_castle(board, move);
    else if (move->flags & PROMOTION)   //TODO get rid of explicit promotion flag pass
    {
        remove_piece(board, move->piece, board->active, move->sourceFile, move->sourceRank);
        add_piece(board, QUEEN, board->active, move->targetFile, move->targetRank);
    }
    else
    {
        remove_piece(board, move->piece, board->active, move->sourceFile, move->sourceRank);
        add_piece(board, move->piece, board->active, move->targetFile, move->targetRank);
        update_castling_rights(board, move);
    }

    // Increment full-move count
    if (board->active == BLACK) board->moveCount++;

    // Set side-to-move
    board->active ^= 1;

    // Update Fifty-Move Rule
    if (capture || move->piece == PAWN || (move->flags & PROMOTION))
        board->halfmoveClock = 0;   // Reset on capture/pawn move
    else board->halfmoveClock++;    // Increment otherwise

     board->zobristKey = compute_zobrist(board);
     move->zobristKey = board->zobristKey;
}

void undo_move(Board *board, const Move *move)
{
    // Set side-to-move
    board->active ^= 1;

    if (move->flags & KING_CASTLE || move->flags & QUEEN_CASTLE)
        undo_castle(board, move);
    else if (move->flags & PROMOTION)
    {
        remove_piece(board, QUEEN, board->active, move->targetFile, move->targetRank);
        add_piece(board, move->piece, board->active, move->sourceFile, move->sourceRank);
    }
    else
    {
        remove_piece(board, move->piece, board->active, move->targetFile, move->targetRank);
        add_piece(board, move->piece, board->active, move->sourceFile, move->sourceRank);
    }

    if (move->captured != NO_PIECE)
        add_piece(board, move->captured, !board->active, move->targetFile, move->targetRank);

    //Reset castle rights
    board->castleRights = move->castleRights;

    // Increment full-move count
    if (board->active == BLACK) board->moveCount--;

    //Reset halfmove clock
    board->halfmoveClock = move->halfmoveClock;

    board->zobristKey = compute_zobrist(board);
}