//
// Created by ernad on 12/29/25.
//

#ifndef ACC_ENGINE_FEN_H
#define ACC_ENGINE_FEN_H

Board parse_fen(const char* fen);

char* board_to_fen(Board board);

#endif //ACC_ENGINE_FEN_H
