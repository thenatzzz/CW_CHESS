#ifndef KING_H
#define KING_H

#include "Piece.h"

class Position;
class ChessBoard;

class King: public Piece{
 public:
  King(Color color, Position *position, ChessBoard *board);
  ~King();

  bool isValidMoveIndividualPiece(Position *next_position);//check King's move and make sure it will not put King in check position
  bool isMoveOneAnyDirection(int rank_distance, int file_distance);// check whether King moves in just one square in every direction
  bool isInCheck();
  bool isInCheckmate();// check whether player's king is in checkmate situation or not
  Position* getEnemyAttackKingPosition();// get position of opponent's piece that threaten our King
  bool canGetOutOfCheck(); //check possible moves that player's King can move out of check situation
  bool takePieceThreatenKing();//check whether player's piece can take off opponent's piece threatening player's King
  bool putKingOutOfCheck();  //check whether player's piece can protect King or not (like blocking opponent move)
};

#endif
