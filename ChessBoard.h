#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <map>
#include <string>

#include "Position.h"

class Bishop;
class King;
class Knight;
class Pawn;
class Queen;
class Rook;
class Piece;
class Position;

#define INVALID_INITIAL_POSITION 0
#define WRONG_PLAYER 1
#define CAPTURE_OWNN_PIECE 2
#define CANNOT_GET_PIECE 3
#define GAME_OVER 4
#define OUT_OF_BOARD_BOUNDARY 5
#define CHECKMATE 6
#define CHECK 7
#define TAKE_DOWN 8
#define NO_PIECE_AT_THIS_POSITION 9
#define MOVE 10
#define INVALID_DESTINATION 11
#define GAME_START 12

// there are 2 players: we assume WHITE always moves first
enum PLAYER{ BLACK_PLAYER, WHITE_PLAYER};

class ChessBoard{
 private:
  Bishop *black_Bishop_C,*black_Bishop_F;
  King   *black_King;
  Knight *black_Knight_B,*black_Knight_G;
  Pawn   *black_Pawn_A,*black_Pawn_B,*black_Pawn_C,*black_Pawn_D,
    *black_Pawn_E,*black_Pawn_F,*black_Pawn_G,*black_Pawn_H;
  Queen  *black_Queen;
  Rook   *black_Rook_A,*black_Rook_H;

  Bishop *white_Bishop_C,*white_Bishop_F;
  King   *white_King;
  Knight *white_Knight_B,*white_Knight_G;
  Pawn   *white_Pawn_A,*white_Pawn_B,*white_Pawn_C,*white_Pawn_D,
    *white_Pawn_E,*white_Pawn_F,*white_Pawn_G,*white_Pawn_H;
  Queen  *white_Queen;
  Rook   *white_Rook_A,*white_Rook_H;

  PLAYER current_player;
  bool game_ended;

  void deletePieces();
  void setUpBoard(); // dynamically create each piece and insert it into STL::map

 public:
  static const int BOARD_WIDTH = 8;
  static const int BOARD_LENGTH = 8;

  // map to store each position and individual piece in first and second aargument accordingly
  // third argument is used for arranging map key(Position) from lowest position to highest positon (0,1,2,...,7)
  std::map<Position, Piece*, Position::less_than_functor> map_pieces;

  ChessBoard();
  ~ChessBoard(); // Destructor will invoke delete function to free memory in the heap (chess piece we dynamically created in heap)

  bool isValidPosition(Position *position); // check whether position submitted by user is on the board or not
  void switchPlayers();// switch player after player successfully submits move
  void resetBoard();
  void submitMove(const char* initial_square, const char* next_square);
  PLAYER getPlayer();  // get current player
  std::string getPlayerColor();
  std::string getEnemyColor();
  Piece* getPieceAtPosition(Position *position);
  bool isEmptyAt(Position *position);
  bool isEnemyKingInCheck(); // check whether opponent's King in check or not, if true we can go on and check whether it is check mate or not
  bool isEnemyKingInCheckmate();
  bool isPlayerKingInCheck(); // check our own King like above function

  // use function overwriting method because each message receive different parameters
  void giveMessage(int message_code);
  void giveMessage(int message_code, Position *position);
  void giveMessage(int message_code, const char* initial_square);
  void giveMessage(int message_code, const char* initial_square, const char* next_square, Piece* piece);
  void giveMessage(int message_code, const char* next_square, Piece *piece);
};

#endif
