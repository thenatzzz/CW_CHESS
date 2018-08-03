#include <string>
#include <iostream>

#include "ChessBoard.h"
#include "Position.h"

#include "King.h"

using namespace std;

King::King(Color color, Position *position, ChessBoard *board)
  : Piece(color, position, board){
  piece_name = "King";
}

King::~King(){
}

bool King::isValidMoveIndividualPiece(Position *next_position){

  int rank_difference = position->getRankDiffDistance(next_position);
  int file_difference = position->getFileDiffDistance(next_position);

  //Initial check for King move: King can only move one sqr in any direction( vertical, diagonal, horizontal)
  if( isMoveOneAnyDirection(rank_difference, file_difference) 
     && ( isDiagonalMove(rank_difference, file_difference)
	|| isVerticalMove(rank_difference, file_difference)
	|| isHorizontalMove(rank_difference, file_difference) ) ){

    // Return true if submitted King move does not put player's King in check
    return isValidPosNextMove(next_position);
  }

  return false;
}

bool King::isMoveOneAnyDirection(int rank_distance, int file_distance){

  if(  (abs(rank_distance) >= 0 && abs(rank_distance)<= 1)
       &&(abs(file_distance) >= 0 && abs(file_distance) <= 1)){
    return true;
  }
  return false;
}

bool King::isInCheck(){
  
  //Iterate through the map to check that opponent's pieces( the pieces having different color than player's) can move on to King's position
  for(map<Position, Piece*>::iterator it = board->map_pieces.begin(); it != board->map_pieces.end(); ++it){
    Piece *enemy_piece = it->second;
    if(!hasSameColor(enemy_piece) && enemy_piece->isValidMoveIndividualPiece(position)){
      return true;      
    }
  }
  return false;
}

bool King::takePieceThreatenKing(){

  // This function checks whether our piece can capture opponent's piece which threatens our King:
  // 1. We get opponent's piece position
  // 2. We iterate through map to get our piece and check whether it can move onto opponet's piece or not
  
  Position *position_enemy_piece = getEnemyAttackKingPosition();

  for(map<Position, Piece*>::iterator it = board->map_pieces.begin(); it != board->map_pieces.end(); ++it) {

    Piece *our_piece = it->second;
    if(hasSameColor(our_piece) && our_piece->isValidMoveIndividualPiece(position_enemy_piece))
      return true;
  }
  return false;
}

bool King::putKingOutOfCheck(){

  Position *position_enemy_piece = getEnemyAttackKingPosition();

  for(map<Position, Piece*>::iterator it = board->map_pieces.begin(); it != board->map_pieces.end(); ++it) {
    
    // This function checks whether our piece can put our King out of check
    Piece *our_piece = it->second;

    if(hasSameColor(our_piece)) {

      for(int file = 0; file < board->BOARD_WIDTH-1; file++ ) {
	for(int rank = 0; rank < board->BOARD_LENGTH-1; rank++ ) {

	  if(our_piece->isValidMoveIndividualPiece(position_enemy_piece)) {
	    return true;
	  }
	}
      }
    }
  }
  return false;
}

bool King::isInCheckmate(){

  if( putKingOutOfCheck() || takePieceThreatenKing() || canGetOutOfCheck() )
    return false;

  return true;
}

Position* King::getEnemyAttackKingPosition(){

  // We iterate though the map and try to get position of enemy's piece that threatens our King (the piece that does not have same color as ours)
  for(std::map<Position, Piece*>::iterator it = board->map_pieces.begin(); it != board->map_pieces.end(); ++it){
    
    Piece *piece = it->second;

    if(!hasSameColor(piece) && piece->isValidMoveIndividualPiece(position)){
	return piece->getPosition();     
    }
  }
  
  board->giveMessage(CANNOT_GET_PIECE);
  return NULL;
}

bool King::canGetOutOfCheck(){
  
  // In this function: we try to find out whether our King can move out of threantened position by itself (either moving to non-threatening position or capturing enemy's piece)
  int file_index =  position->getFileIndex();
  int rank_index =  position->getRankIndex();
  
  // index starts from with -1 and constraint starts from +1 so we can check King possible move ( we don't need to be worried about out of board direction as we did error checking before ) 
  for(int file = file_index -1; file <= file_index+1 && file < board->BOARD_WIDTH -1; file++){
    for(int rank = rank_index -1; rank <= rank_index+1 && rank < board->BOARD_LENGTH-1; rank++){

      if(file_index == file && rank_index == rank) // the current position of King
	continue;

      Position *king_clone_position = new Position(file,rank);

      if(isValidMoveIndividualPiece(king_clone_position)
	 && (isCaptureEnemyPiece(king_clone_position) || board->isEmptyAt(king_clone_position))){
	delete king_clone_position;
	return true;
      }

      if(board->isEmptyAt(king_clone_position)){
	delete king_clone_position;
      }
    }
  }
  return false;
}
