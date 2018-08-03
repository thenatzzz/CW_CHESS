#include <iostream>
#include <stdio.h>

#include "Position.h"
#include "ChessBoard.h"

//Constructor for: each individual piece simulated move
Position::Position(int file_index, int rank_index)
  : file(file_index + 'A'),
    file_index(file_index),
    rank_index(rank_index){
    }

//Constructor for: position User put in
Position::Position(const char *position) // pass in position (string like 'A8')
  : file(toupper(position[0])),
    file_index(toupper(position[0])-'A'), // index 0,1,2,...,7
    rank_index(position[1]-'0'-1){    // index 0,1,2,...,7
  // note: need to minus 1 because User input starts from 1
}

Position::~Position(){

}

const int Position::getFileIndex() const{
  return file_index;
}

const int Position::getRankIndex() const{
  return rank_index;
}

bool Position::isPositionOnBoard(ChessBoard *board){
  if( (file_index >= 0 && file_index < board->BOARD_LENGTH)
      &&(rank_index >= 0 && rank_index < board->BOARD_WIDTH)){
    return true;
  }
  return false;
}

int Position::getFileDiffDistance(Position *position){
  return file_index - position->file_index;
}

int Position::getRankDiffDistance(Position *position){
  return rank_index - position->rank_index;
}

bool Position::overloadSmall(Position *position){
  if( file_index < position->file_index
      ||(file_index == position->file_index && rank_index < position->rank_index)){
    return true;
  }
  return false;
}
