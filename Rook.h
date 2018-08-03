#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
 public:
  Rook(Color color, Position *position, ChessBoard *board);
  ~Rook();
  bool isValidMoveIndividualPiece(Position *next_position); //check Rook's move and make sure it will not put King in check position
  bool isRookValidMove(int rank_distance, int file_distance);// check Rook's basic move 
};

#endif
