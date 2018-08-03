#include <iostream>

#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

#include "ChessBoard.h"

using namespace std;

ChessBoard::ChessBoard()
  : current_player(WHITE_PLAYER), game_ended(false){
  
  setUpBoard();
}

ChessBoard::~ChessBoard(){
  deletePieces();
}

void ChessBoard::setUpBoard(){

  giveMessage(GAME_START);

  // each pointer to piece dynamically create piece in heap then
  // inject color, dynamically create particular position according to Chess game format ,and finally inject memory location of board (so each piece can interact in the same board)
  black_Bishop_C = new Bishop(BLACK, new Position("C8"), this);
  black_Bishop_F = new Bishop(BLACK, new Position("F8"), this);
  black_King    = new King(BLACK,   new Position("E8"), this);
  black_Knight_B = new Knight(BLACK, new Position("B8"), this);
  black_Knight_G = new Knight(BLACK, new Position("G8"), this);
  black_Pawn_A   = new Pawn(BLACK,   new Position("A7"), this);
  black_Pawn_B   = new Pawn(BLACK,   new Position("B7"), this);
  black_Pawn_C   = new Pawn(BLACK,   new Position("C7"), this);
  black_Pawn_D   = new Pawn(BLACK,   new Position("D7"), this);
  black_Pawn_E   = new Pawn(BLACK,   new Position("E7"), this);
  black_Pawn_F   = new Pawn(BLACK,   new Position("F7"), this);
  black_Pawn_G   = new Pawn(BLACK,   new Position("G7"), this);
  black_Pawn_H   = new Pawn(BLACK,   new Position("H7"), this);
  black_Queen   = new Queen(BLACK,  new Position("D8"), this);
  black_Rook_A   = new Rook(BLACK,   new Position("A8"), this);
  black_Rook_H   = new Rook(BLACK,   new Position("H8"), this);

  white_Bishop_C = new Bishop(WHITE, new Position("C1"), this);
  white_Bishop_F = new Bishop(WHITE, new Position("F1"), this);
  white_King    = new King(WHITE,   new Position("E1"), this);
  white_Knight_B = new Knight(WHITE, new Position("B1"), this);
  white_Knight_G = new Knight(WHITE, new Position("G1"), this);
  white_Pawn_A   = new Pawn(WHITE,   new Position("A2"), this);
  white_Pawn_B   = new Pawn(WHITE,   new Position("B2"), this);
  white_Pawn_C   = new Pawn(WHITE,   new Position("C2"), this);
  white_Pawn_D   = new Pawn(WHITE,   new Position("D2"), this);
  white_Pawn_E   = new Pawn(WHITE,   new Position("E2"), this);
  white_Pawn_F   = new Pawn(WHITE,   new Position("F2"), this);
  white_Pawn_G   = new Pawn(WHITE,   new Position("G2"), this);
  white_Pawn_H   = new Pawn(WHITE,   new Position("H2"), this);
  white_Queen   = new Queen(WHITE,  new Position("D1"), this);
  white_Rook_A   = new Rook(WHITE, new Position("A1"), this);
  white_Rook_H   = new Rook(WHITE,    new Position("H1"), this);

  // After setting up each piece with particular initial position, we now can put them in STL::map
  // note: use insert with value_type to avoid invoking copy constructor
  map_pieces.insert(map<Position,Piece*>::value_type(*(black_Bishop_C->getPosition()), black_Bishop_C));
  map_pieces.insert(map<Position,Piece*>::value_type(*(black_Bishop_F->getPosition()), black_Bishop_F));
  map_pieces.insert(map<Position,Piece*>::value_type(*(black_King->getPosition()), black_King));
  map_pieces.insert(map<Position,Piece*>::value_type(*(black_Knight_B->getPosition()), black_Knight_B));
  map_pieces.insert(map<Position,Piece*>::value_type(*(black_Knight_G->getPosition()), black_Knight_G));
  map_pieces.insert(map<Position,Piece*>::value_type(*(black_Pawn_A->getPosition()), black_Pawn_A));
  map_pieces.insert(map<Position,Piece*>::value_type(*(black_Pawn_B->getPosition()), black_Pawn_B));
  map_pieces.insert(map<Position,Piece*>::value_type(*(black_Pawn_C->getPosition()), black_Pawn_C));
  map_pieces.insert(map<Position,Piece*>::value_type(*(black_Pawn_D->getPosition()), black_Pawn_D));
  map_pieces.insert(map<Position,Piece*>::value_type(*(black_Pawn_E->getPosition()), black_Pawn_E));
  map_pieces.insert(map<Position,Piece*>::value_type(*(black_Pawn_F->getPosition()), black_Pawn_F));
  map_pieces.insert(map<Position,Piece*>::value_type(*(black_Pawn_G->getPosition()), black_Pawn_G));
  map_pieces.insert(map<Position,Piece*>::value_type(*(black_Pawn_H->getPosition()), black_Pawn_H));
  map_pieces.insert(map<Position,Piece*>::value_type(*(black_Queen->getPosition()), black_Queen));
  map_pieces.insert(map<Position,Piece*>::value_type(*(black_Rook_A->getPosition()), black_Rook_A));
  map_pieces.insert(map<Position,Piece*>::value_type(*(black_Rook_H->getPosition()), black_Rook_H));

  map_pieces.insert(map<Position,Piece*>::value_type(*(white_Bishop_C->getPosition()), white_Bishop_C));
  map_pieces.insert(map<Position,Piece*>::value_type(*(white_Bishop_F->getPosition()), white_Bishop_F));
  map_pieces.insert(map<Position,Piece*>::value_type(*(white_King->getPosition()), white_King));
  map_pieces.insert(map<Position,Piece*>::value_type(*(white_Knight_B->getPosition()), white_Knight_B));
  map_pieces.insert(map<Position,Piece*>::value_type(*(white_Knight_G->getPosition()), white_Knight_G));
  map_pieces.insert(map<Position,Piece*>::value_type(*(white_Pawn_A->getPosition()), white_Pawn_A));
  map_pieces.insert(map<Position,Piece*>::value_type(*(white_Pawn_B->getPosition()), white_Pawn_B));
  map_pieces.insert(map<Position,Piece*>::value_type(*(white_Pawn_C->getPosition()), white_Pawn_C));
  map_pieces.insert(map<Position,Piece*>::value_type(*(white_Pawn_D->getPosition()), white_Pawn_D));
  map_pieces.insert(map<Position,Piece*>::value_type(*(white_Pawn_E->getPosition()), white_Pawn_E));
  map_pieces.insert(map<Position,Piece*>::value_type(*(white_Pawn_F->getPosition()), white_Pawn_F));
  map_pieces.insert(map<Position,Piece*>::value_type(*(white_Pawn_G->getPosition()), white_Pawn_G));
  map_pieces.insert(map<Position,Piece*>::value_type(*(white_Pawn_H->getPosition()), white_Pawn_H));
  map_pieces.insert(map<Position,Piece*>::value_type(*(white_Queen->getPosition()), white_Queen));
  map_pieces.insert(map<Position,Piece*>::value_type(*(white_Rook_A->getPosition()), white_Rook_A));
  map_pieces.insert(map<Position,Piece*>::value_type(*(white_Rook_H->getPosition()), white_Rook_H));
}

void ChessBoard::resetBoard(){

  // reset players: make WHITE_PLAYER moves first
  current_player = WHITE_PLAYER;
  game_ended = false;
  deletePieces();
  setUpBoard();
}

void ChessBoard::switchPlayers(){
  if(current_player == WHITE_PLAYER)
    current_player = BLACK_PLAYER;
  else
    current_player = WHITE_PLAYER;
}

void ChessBoard::deletePieces(){
  delete black_Bishop_C;
  delete black_Bishop_F;
  delete black_King;
  delete black_Knight_B;
  delete black_Knight_G;
  delete black_Pawn_A;
  delete black_Pawn_B;
  delete black_Pawn_C;
  delete black_Pawn_D;
  delete black_Pawn_E;
  delete black_Pawn_F;
  delete black_Pawn_G;
  delete black_Pawn_H;
  delete black_Queen;
  delete black_Rook_A;
  delete black_Rook_H;

  delete white_Bishop_C;
  delete white_Bishop_F;
  delete white_King;
  delete white_Knight_B;
  delete white_Knight_G;
  delete white_Pawn_A;
  delete white_Pawn_B;
  delete white_Pawn_C;
  delete white_Pawn_D;
  delete white_Pawn_E;
  delete white_Pawn_F;
  delete white_Pawn_G;
  delete white_Pawn_H;
  delete white_Queen;
  delete white_Rook_A;
  delete white_Rook_H;

  map_pieces.clear();
}

bool ChessBoard::isValidPosition(Position *position){
  return position->isPositionOnBoard(this);
}

void ChessBoard::giveMessage(int message_code){
  switch(message_code){
  case INVALID_INITIAL_POSITION:
    cout << "ERROR: Invalid initial position."<<endl;
    break;
  case WRONG_PLAYER:
    cout <<"It is not "<< this->getEnemyColor() << "'s turn to move!"<< endl;
    break;
  case CAPTURE_OWNN_PIECE:
    cout << this->getPlayerColor()<< " cannot capture one of its own piece!"<< endl;
    break;
  case CANNOT_GET_PIECE:
    cout << "ERROR: Cannot get checking piece."<< endl;
    break;
  case GAME_OVER:
    cout << "The game is over!"<< endl;
    break;
  case OUT_OF_BOARD_BOUNDARY:
    cout << "ERROR: Cannot move out of board."<< endl;
    break;
  case CHECKMATE:
    cout<< getEnemyColor() <<" is in checkmate"<< endl;
    break;
  case CHECK:
    cout << getEnemyColor() << " is in check"<< endl;
    break;
  case GAME_START:
    cout <<"A new chess game is started!"<< endl;
    break;
  }
}

void ChessBoard::giveMessage(int message_code, Position *position){
  switch(message_code){
  case TAKE_DOWN:
    cout << " taking "<< this->getEnemyColor() <<"'s "
	 <<this->getPieceAtPosition(position)->getPieceName();
    break;
  }
}

void ChessBoard::giveMessage(int message_code, const char* initial_square){
  switch(message_code){
  case NO_PIECE_AT_THIS_POSITION:
    cout << "There is no piece at position "<< initial_square << "!"<< endl;
    break;
  }
}

void ChessBoard::giveMessage(int message_code, const char* initial_square, const char* next_square, Piece* piece){

  switch(message_code){
  case MOVE:
    cout << getPlayerColor() <<"'s "<<piece->getPieceName()<<" moves from "
	 << initial_square<<" to "<< next_square;
    break;
  }
}

void ChessBoard::giveMessage(int message_code,const char* next_square, Piece *piece){
  switch(message_code){
  case INVALID_DESTINATION:
    cout << getPlayerColor()<< "'s "<< piece->getPieceName()<<" cannot move to "
	 << next_square <<"!"<< endl;
    break;
  }
}

void ChessBoard::submitMove(const char* initial_square, const char* next_square){
  if(game_ended){
    giveMessage(GAME_OVER);
    return;
  }
  
  // dynamically create new object (Position class), so we can easily manipulate position since Position class is shared among individual piece and chess board
  Position *current_position = new Position(initial_square);
  Position *next_position = new Position(next_square);

  // Initial check whether User grabs piece on board and places it on board or not, if not we don't need to go further
  if(!isValidPosition(current_position) || !isValidPosition(next_position)){
    giveMessage(OUT_OF_BOARD_BOUNDARY);
  }

  if(isEmptyAt(current_position)){
    this->giveMessage(NO_PIECE_AT_THIS_POSITION, initial_square);

  }else{
    Piece *piece = NULL;
    piece = getPieceAtPosition(current_position);

    // this is basic check that : 1.whether User grabs his own color piece or not
    //                            2.whether User submits the move that captures his own piece
    // note: putting 1. and 2. into function so it is easier to print out error message
    if(piece->isValidMoveForAnyPiece(next_position)){

      // check basic move for individual piece and make sure it not make King in check position
      if(piece->isValidMoveIndividualPiece(next_position)){
       
	giveMessage(MOVE, initial_square,next_square, piece);

	//if we can pass all the error checking part, we can update position (putting new position in map and deleting old position)
	piece->updatePosition(next_position);
	cout << endl;

	if(isEnemyKingInCheck()){
	  if(isEnemyKingInCheckmate()){
	    giveMessage(CHECKMATE);
	    game_ended = true;
	  }else{
	    giveMessage(CHECK);
	  }
	}

	switchPlayers();
      }else{
	giveMessage(INVALID_DESTINATION,next_square, piece);
      }
    }
  }

  if(isEmptyAt(next_position)){
    delete next_position;
  }

  delete current_position;
}

PLAYER ChessBoard::getPlayer(){
  return current_player;
}

string ChessBoard::getPlayerColor(){
  if(current_player == WHITE_PLAYER)
    return "White";
  return "Black";
}

string ChessBoard::getEnemyColor(){
  if(current_player == WHITE_PLAYER)
    return "Black";
  return "White";
}

Piece* ChessBoard::getPieceAtPosition(Position *position){
  for(map<Position, Piece*>::iterator it = map_pieces.begin(); it != map_pieces.end(); ++it){
    
    if(  it->first.getFileIndex() == position->getFileIndex()
	 &&it->first.getRankIndex() == position->getRankIndex()){
      return it->second;
    }  
  }
  return NULL;
}

bool ChessBoard::isEmptyAt(Position *position){
  map<Position, Piece*>::iterator it = map_pieces.find(*position);
  return it == map_pieces.end() || it->second == NULL;
}

bool ChessBoard::isEnemyKingInCheck(){
  return (current_player == BLACK_PLAYER && white_King->isInCheck())
    || (current_player == WHITE_PLAYER && black_King->isInCheck());
}

bool ChessBoard::isEnemyKingInCheckmate(){
  if(!isEnemyKingInCheck()){
    return false;
  }

  if( current_player == BLACK_PLAYER && white_King->isInCheckmate()){
    return true;
  }else if(current_player == WHITE_PLAYER && black_King->isInCheckmate()){
    return true;
  }

  return false;
}

bool ChessBoard::isPlayerKingInCheck(){
  return (current_player == WHITE_PLAYER && white_King->isInCheck())
    || (current_player == BLACK_PLAYER && black_King->isInCheck());
}
