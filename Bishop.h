#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece{
 public:
  Bishop(Color color, Position *position, ChessBoard *board);
  ~Bishop();
  bool isValidMoveIndividualPiece(Position *next_position);// check valid move for Bishop
};

#endif
