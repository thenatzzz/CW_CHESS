#include "ChessBoard.h"
#include "Position.h"

#include "Rook.h"

using namespace std;

Rook::Rook(Color color, Position *position, ChessBoard *board)
  : Piece(color, position, board) {
  piece_name = "Rook";
}

Rook::~Rook(){
}

bool Rook::isRookValidMove(int rank_distance, int file_distance){
  if(isDiagonalMove(rank_distance,file_distance))
    return false;

  return true;
}

// ################ note: The whole function acts very similar to Queen move except Rook does not have Diagonal move
bool Rook::isValidMoveIndividualPiece(Position *next_position){

  int rank_difference = position->getRankDiffDistance(next_position);
  int file_difference = position->getFileDiffDistance(next_position);

  int move_up_down = 0;
  int move_right_left = 0;

  bool vertical_direction = false;

  if(!isRookValidMove(rank_difference, file_difference)) {
    return false;
  }

  if(isVerticalMove(rank_difference,file_difference)) {

    if(rank_difference<0){
      move_up_down = MOVE_UP_ONEsq;
    }else{
      move_up_down = MOVE_DOWN_ONEsq;
    }
    
    vertical_direction = true;
  }

  if(isHorizontalMove(rank_difference,file_difference)) {

    if(file_difference<0){
      move_right_left = MOVE_RIGHT_ONEsq;
    }else{
      move_right_left = MOVE_LEFT_ONEsq;
    }
    
  }

  int rank = position->getRankIndex() + move_up_down;
  int file = position->getFileIndex() + move_right_left;

  bool empty_square = true;

  if(vertical_direction){

    while(rank != next_position->getRankIndex()){

      Position *clone_position = new Position(file, rank);

      if(!board->isEmptyAt(clone_position)) {
	empty_square = false;
	break;
      } else {
	delete clone_position;
      }

      rank += move_up_down;

    }
  }else{
    while(file != next_position->getFileIndex()){

      Position *clone_position = new Position(file, rank);

      if(!board->isEmptyAt(clone_position)) {
	empty_square = false;
	break;
      } else {
	delete clone_position;
      }

      file += move_right_left;
    }
  }

  if(empty_square) {
    return isValidPosNextMove(next_position);
  }
  return false;
}
