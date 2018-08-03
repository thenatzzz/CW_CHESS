#include <string>
#include <iostream>

#include "ChessBoard.h"
#include "Piece.h"

using namespace std;

Piece::Piece(Color color, Position *position, ChessBoard *board){

  //Initial check for piece set-up, if user puts piece out of board, game fails
  if(!position->isPositionOnBoard(board)){
    board->giveMessage(INVALID_INITIAL_POSITION);
  }

  this->color = color;
  this->position = position;
  this->board = board;
}

Piece::~Piece(){
  delete position;
}

string Piece::getPieceName(){
  return piece_name;
}

Position* Piece::getPosition(){
  return position;
}

bool Piece::hasPlayerColor(){
  if( (board->getPlayer() == WHITE_PLAYER && color == WHITE)
      ||(board->getPlayer() == BLACK_PLAYER && color == BLACK) ){
    return true;
  }
  return false;
}

bool Piece::hasEnemyColor(){
  if( (board->getPlayer() == BLACK_PLAYER && color == WHITE)
      ||(board->getPlayer() == WHITE_PLAYER && color == BLACK) ){
    return true;
  }
  return false;
}

bool Piece::hasSameColor(Piece *piece){
  return piece->color == color;
}

// acting as the most basic error checking for every piece
bool Piece::isValidMoveForAnyPiece(Position *position){

  if(hasEnemyColor()){
    board->giveMessage(WRONG_PLAYER);
    return false;
  }

  if(isCaptureOwnPiece(position)){
    board->giveMessage(CAPTURE_OWNN_PIECE);
    return false;
  }
  return true;
}

bool Piece::isCaptureOwnPiece(Position *position){
  if( !board->isEmptyAt(position)
      && hasSameColor(board->getPieceAtPosition(position)) ){
    return true;
  }
  return false;
}

bool Piece::isCaptureEnemyPiece(Position *position){
  if( !board->isEmptyAt(position)
      && !hasSameColor(board->getPieceAtPosition(position)) ){
    return true;
  }
  return false;
}

void Piece::updatePosition(Position *new_position){
  // In this update function: we take 2 cases in consideration:
  // 1. whether the next position is occupied by opponent's piece; if it is, we do update position by removing opponent's piece off the map and putting our updated-piece position into instead (removing old-piece position in map as well)
  // 2. whether the next position is empty; if it is, we put our updated-piece position into map and remove old-piece position in map.
  // note: we need to make sure that our piece pointer points to new position and deallocates old position.

  if( isCaptureEnemyPiece(new_position)){

    board->giveMessage(TAKE_DOWN, new_position);// remove enemy's position from map
    board->map_pieces.erase(*new_position); // in this case: new_position refers to opponent's position

    board->map_pieces.erase(*(this->position)); // remove our old position

    delete this->position;         //deallocate pointer to old position
    this->position = new_position; // relocate it to new position

    // insert new position inside map
    board->map_pieces.insert(map<Position,Piece*>::value_type(*(this->position),this));
  }else{

    board->map_pieces.erase(*(this->position));

    delete this->position;
    this->position = new_position;

    board->map_pieces.insert(map<Position,Piece*>::value_type(*(this->position),this));
  }
}


bool Piece::isValidPosNextMove(Position *position){
  // this is the most important function to check that any piece can move and make sure it does not put King in check position
  // We simulate the move by creating temporary piece.
  
  bool result = false;

  Piece *piece_new_position = NULL;

  // this function helps check whether position is empty or not (so we don't access wrong memory.
  if(!board->isEmptyAt(position)){

    piece_new_position = board->getPieceAtPosition(position);
    board->map_pieces.erase(*position);
  }

  //We temporarily erase old position from map
  board->map_pieces.erase(*(this->position));

  // create position object to store(point to) old position for later use
  Position *old_position = this->position;

  //We point old position to next position, then store into map in order to use board function
  this->position = position;
  board->map_pieces.insert(map<Position,Piece*>::value_type(*(this->position),this));

  // check that the next position does not put player in Check position
  if((hasPlayerColor() && !board->isPlayerKingInCheck())
     || (hasEnemyColor() && !board->isEnemyKingInCheck())) {
    result = true;
  }

  board->map_pieces.erase(*(this->position));

  // We point back to old positon and insert back into map
  this->position = old_position;
  board->map_pieces.insert(map<Position,Piece*>::value_type(*(this->position),this));

  // if piece at the new position passes all our check, we put it into map
  if(piece_new_position){
    board->map_pieces.insert(map<Position,Piece*>::value_type(*position,piece_new_position));
  }
  return result;
}

bool Piece::isDiagonalMove(int rank_distance, int file_distance){
  if(abs(rank_distance)== abs(file_distance))
    return true;
  return false;
}

bool Piece::isVerticalMove(int rank_distance, int file_distance){
  if(abs(rank_distance)>0  && abs(file_distance) == 0)
    return true;
  return false;
}

bool Piece::isHorizontalMove(int rank_distance, int file_distance){
  if(abs(rank_distance)==0  && abs(file_distance) >0)
    return true;
  return false;
}
