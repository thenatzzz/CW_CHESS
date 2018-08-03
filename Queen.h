#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Position;
class ChessBoard;

class Queen : public Piece {
 public:
  Queen(Color color, Position *position, ChessBoard *board);
  virtual ~Queen();
  bool isValidMoveIndividualPiece(Position *next_position);//check Queen's move and make sure it will not put King in check position
  bool isQueenValidMove(int rank_distance,int file_distance); // check Queen's basic move
};

#endif
