#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Position;
class ChessBoard;

class Pawn : public Piece {
 public:
  Pawn(Color color, Position *position, ChessBoard *board);
  ~Pawn();
  //check Pawn's move and make sure it will not put King in check position
  bool isValidMoveIndividualPiece(Position *next_position);
  // check whether it can move 2 sqr (initial position) or not
  bool isValidFirstMove(int rank_distance, int file_distance,Position *next_position, int moving_direction);
  // check whether it can capture opponent's piece or not
  bool isValidDiagonalMove(int rank_distance, int file_distance,Position *next_position, int moving_direction);
  // check normal move of Pawn (one square)
  bool isValidNormalMove(int rank_distance, int file_distance, Position *next_position, int moving_direction);
};

#endif
