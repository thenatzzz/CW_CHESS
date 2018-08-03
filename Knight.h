#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Position;
class ChessBoard;

class Knight : public Piece {
 public:
  Knight(Color color, Position *position, ChessBoard *board);
  ~Knight();
  bool isValidMoveIndividualPiece(Position *next_position);  //check Knight's move and make sure it will not put King in check position
  bool isKnightValidMove(int rank_distance, int file_distance); // check whether it is Knight's normal move or not (Lshaped move)
};

#endif
