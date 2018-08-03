#include "ChessBoard.h"
#include "Position.h"

#include "Queen.h"

using namespace std;

Queen::Queen(Color color, Position *position, ChessBoard *board)
  : Piece(color, position, board) {
  piece_name = "Queen";
}

Queen::~Queen(){

}

bool Queen::isQueenValidMove(int rank_distance,int file_distance){

  // check Queen normal move (vertically, horizontally, diagonally)
  if(  isVerticalMove(rank_distance, file_distance)
       ||isHorizontalMove(rank_distance,file_distance)
       ||isDiagonalMove(rank_distance, file_distance)  ){
    return true;
  }

  return false;
}

bool Queen::isValidMoveIndividualPiece(Position *next_position){

  int rank_difference = position->getRankDiffDistance(next_position);
  int file_difference = position->getFileDiffDistance(next_position);

  int move_up_down = 0;
  int move_right_left = 0;

  //Flags set for checking direction of Queen move
  bool vertical_direction = false;
  bool horizontal_direction = false;

  if(!isQueenValidMove(rank_difference, file_difference)){
    return false;
  }

  //These 3 if-conditions check direction of Queen and assign 1 to it for later use.
  
  //Queen moves up when new position has higher rank than old position (we assign one to index) and sets flags
  if(isVerticalMove(rank_difference, file_difference)) {

    if(rank_difference<0){
      move_up_down = MOVE_UP_ONEsq;
    }else{
      move_up_down = MOVE_DOWN_ONEsq;
    }
    
    vertical_direction = true;
  }
  //Queen moves right when new position has higher file than old position (we assign one to index) and sets flags
  if(isHorizontalMove(rank_difference, file_difference)) {

    if(file_difference<0){
      move_right_left = MOVE_RIGHT_ONEsq;
    }else{
      move_right_left = MOVE_LEFT_ONEsq;
    }
    
    horizontal_direction = true;
  }
  //Combine both of aboev statement 
  if(isDiagonalMove(rank_difference, file_difference)) {

    if(rank_difference<0){
      move_up_down = MOVE_UP_ONEsq;
    }else{
      move_up_down = MOVE_DOWN_ONEsq;
    }

    if(file_difference<0){
      move_right_left = MOVE_RIGHT_ONEsq;
    }else{
      move_right_left = MOVE_LEFT_ONEsq;
    }
    
    horizontal_direction = true;
    vertical_direction = true;
  }

  int rank = position->getRankIndex() + move_up_down;
  int file = position->getFileIndex() + move_right_left;

  bool empty_square = true;

  // We first check the direction the Queen move then gradually check one square by one square until reaching desired next position
  //(if Queen hits some piece along the way before reaching desired position, we break out of loops)
  
  if(vertical_direction && horizontal_direction){

    while(rank != next_position->getRankIndex() && file != next_position->getFileIndex()){

      Position *clone_position = new Position(file, rank);

      if(!board->isEmptyAt(clone_position)) {
	empty_square = false;
	break;
      } else {
	delete clone_position;
      }

      rank += move_up_down;
      file += move_right_left;
    }
  }else if( horizontal_direction){

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
  }else{

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
  }

  // If the position is empty, we can check the move that does not put our King in check
  if(empty_square) {
    return isValidPosNextMove(next_position);
  }

  return false;
}
