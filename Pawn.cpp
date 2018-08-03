#include <string>
#include <iostream>

#include "ChessBoard.h"
#include "Position.h"

#include "Pawn.h"

using namespace std;

Pawn::Pawn(Color color, Position *position, ChessBoard *board)
  : Piece(color, position, board) {
  piece_name = "Pawn";
}

Pawn::~Pawn(){

}

bool Pawn::isValidFirstMove(int rank_distance, int file_distance,Position *next_position, int moving_direction){

  bool initial_move = false;

  // Check for initial move : WHITE Pawn sit at rank 1 while BLACK Pawn sti at rank 6
  if(  (position->getRankIndex() == 1  && color==WHITE)
     ||(position->getRankIndex() ==6 && color==BLACK) ){
    initial_move = true;
  }

  // Continue to check that WHITE & BLACK move in correct direction and there is no obstruction in the way
  if(   initial_move
       && board->isEmptyAt(next_position)
       && rank_distance == 2*moving_direction
       && file_distance == 0                  ){
    return true;
  }
  return false;
}

bool Pawn::isValidDiagonalMove(int rank_distance, int file_distance,Position *next_position, int moving_direction){

  // Pawn can only move diagonally only if next position is occupied by opponent's piece
  if(   !board->isEmptyAt(next_position)
	&& !hasSameColor(board->getPieceAtPosition(next_position))
	&& rank_distance == 1*(moving_direction)
	&& abs(file_distance)== 1                             ){
    return true;
  }
  return false;
}

bool Pawn::isValidNormalMove(int rank_distance, int file_distance, Position *next_position, int moving_direction){

  // This function checks Pawn normal move (move forward one direction without obstruction)
  if(   board->isEmptyAt(next_position)
	&& rank_distance == 1*(moving_direction)
	&& file_distance == 0                     ){
    return true;
  }
  return false;
}

bool Pawn::isValidMoveIndividualPiece(Position *next_position){

  int rank_difference = position->getRankDiffDistance(next_position);
  int file_difference = position->getFileDiffDistance(next_position);

  int moving_direction = 0;

  // moving_direction = -1 means that next position is greather than current position (so it implies White Pawn move)
  if( color == WHITE){
    moving_direction = -1;
  }else{
    moving_direction = 1;
  }

  if(   isValidFirstMove(rank_difference,file_difference, next_position, moving_direction)
	||isValidDiagonalMove(rank_difference,file_difference, next_position, moving_direction)
	||isValidNormalMove(rank_difference, file_difference, next_position, moving_direction)  ){

    // simulate position to make sure that Pawn move does not put King in check position
    return isValidPosNextMove(next_position);
  }

  return false;
}
