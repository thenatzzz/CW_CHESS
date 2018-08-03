#include "ChessBoard.h"
#include "Position.h"

#include "Bishop.h"

using namespace std;

Bishop::Bishop(Color color, Position *position, ChessBoard *board)
  : Piece(color, position, board){
  piece_name = "Bishop";
}

Bishop::~Bishop(){
}

bool Bishop::isValidMoveIndividualPiece(Position *next_position){

  int rank_difference = position->getRankDiffDistance(next_position);
  int file_difference = position->getFileDiffDistance(next_position);

  if(!isDiagonalMove(rank_difference, file_difference)){
    return false;
  }

  int move_up_down = 0, move_right_left = 0;

  // if Bishop does not move diagonally, move fails (no further step needed to take)
  if(rank_difference < 0){
    move_up_down = MOVE_UP_ONEsq;
  }else{
    move_up_down = MOVE_DOWN_ONEsq;
  }

  // if rank_difference < 0: it means that new position is greater than old position (index), Bishop will move upward direction.
  if(file_difference < 0){
    move_right_left = MOVE_RIGHT_ONEsq;
  }else{
    move_right_left = MOVE_LEFT_ONEsq;
  }

  // Bishop moves diagonally; thus, we update rank and file at the same time.
  int rank = position->getRankIndex() + move_up_down;
  int file = position->getFileIndex() + move_right_left;

  bool empty_square = true;

  // we simulate the Bishop move one by one square if there is some piece obstructing the way before intended position ( argument passed in), move fails.
  while(rank != next_position->getRankIndex() && file != next_position->getFileIndex()) {
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

  // If the position is empty, we check whether the move puts king in Check or not. If it put King in check position, move fails.
  if(empty_square) {
    return isValidPosNextMove(next_position);
  }

  return false;
}
