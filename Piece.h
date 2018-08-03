#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <cmath>

class Position;
class ChessBoard;

enum Color{ BLACK, WHITE};

class Piece{
 protected:
  std::string piece_name;
  Position *position;
  Color color;
  ChessBoard *board;

 public:
  Piece(Color color, Position *position, ChessBoard *board);
  virtual ~Piece();
  std::string getPieceName();
  Position* getPosition(); // get current position
  bool hasPlayerColor();
  bool hasEnemyColor();
  bool hasSameColor(Piece *piece); // check whether following piece has same color as player
  bool isValidMoveForAnyPiece(Position *position); // this function will check whether player move own piece or not and check whether capture own piece or not
  bool isCaptureOwnPiece(Position *position); // check whether we capture our own piece or not
  bool isCaptureEnemyPiece(Position *position);// check whether we capture opponent's piece or not
  void updatePosition(Position *position); // update new position in map if each piece successfully move.
  bool isValidPosNextMove(Position *position); // function to make sure that each piece move will not put King in check position
  bool isDiagonalMove(int rank_distance, int file_distance); // check whether piece moves diagonally across the board
  bool isVerticalMove(int rank_distance, int file_distance);  // check whether piece moves along the file
  bool isHorizontalMove(int rank_distance, int file_distance);// check whether piece moves along the rank

  virtual bool isValidMoveIndividualPiece(Position *next_position) = 0; // use virtual function because each piece has their own particular move
};

#endif
