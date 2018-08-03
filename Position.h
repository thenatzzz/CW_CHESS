#ifndef POSITION_H
#define POSITION_H

class ChessBoard;

#define MOVE_UP_ONEsq 1
#define MOVE_DOWN_ONEsq -1
#define MOVE_RIGHT_ONEsq 1
#define MOVE_LEFT_ONEsq -1

class Position{
 private:
  const char file;

  const int file_index;
  const int rank_index;

 public:
  struct less_than_functor{
    bool operator()(Position previous_value, Position new_value) const {
      return (&previous_value)->overloadSmall(&new_value);
    }
  };

  Position(int file_index, int rank_index);
  Position(const char *position); // pass in position (string like 'A8')
  ~Position();
  const int getFileIndex() const;
  const int getRankIndex() const;
  bool isPositionOnBoard(ChessBoard *board);  //check whether position is on board or not
  int getFileDiffDistance(Position *position); // get the difference rank distance between new position and old position
  int getRankDiffDistance(Position *position); // get the difference file distance between new position and old position

  // this function does nothing related to Chess Game, it is just called for Third argument in STL::map to arrange map key in low to high order
  bool overloadSmall(Position *position); 

};

#endif
