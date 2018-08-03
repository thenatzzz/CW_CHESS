#include "ChessBoard.h"
#include "Position.h"

#include "Knight.h"

using namespace std;

Knight::Knight(Color color, Position *position, ChessBoard *board)
  : Piece(color, position, board) {
  piece_name = "Knight";
}

Knight::~Knight(){

}

bool Knight::isValidMoveIndividualPiece(Position *next_position){

  int rank_difference = position->getRankDiffDistance(next_position);
  int file_difference = position->getFileDiffDistance(next_position);

  // Initial check for L move
  if(isKnightValidMove(rank_difference, file_difference)) {
    return isValidPosNextMove(next_position);
  }

  return false;
}

bool Knight::isKnightValidMove(int rank_distance, int file_distance){
  if(  (abs(rank_distance) == 2 && abs(file_distance) == 1)
       ||(abs(rank_distance) == 1 && abs(file_distance) == 2) ){
    return true;
  }

  return false;
}
