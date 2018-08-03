chess: ChessMain.o Bishop.o ChessBoard.o King.o Knight.o Pawn.o Piece.o Position.o Queen.o Rook.o
		g++ -Wall -g  ChessMain.o Bishop.o ChessBoard.o King.o Knight.o Pawn.o Piece.o Position.o Queen.o Rook.o -o chess

ChessMain.o: ChessMain.cpp ChessBoard.h
		g++ -Wall -g -c ChessMain.cpp

Bishop.o: Bishop.cpp Bishop.h Piece.h ChessBoard.h Position.h
		g++ -Wall -g -c Bishop.cpp

ChessBoard.o: ChessBoard.cpp Bishop.h Position.h King.h Knight.h Pawn.h Queen.h Rook.h ChessBoard.h
		g++ -Wall -g -c ChessBoard.cpp

King.o: King.cpp Piece.h ChessBoard.h Position.h King.h
		g++ -Wall -g -c King.cpp

Knight.o: Knight.cpp ChessBoard.h Position.h Knight.h Piece.h
		g++ -Wall -g -c Knight.cpp

Pawn.o: Pawn.cpp Piece.h ChessBoard.h Position.h Pawn.h
		g++ -Wall -g -c Pawn.cpp

Piece.o: Piece.cpp ChessBoard.h Piece.h
		g++ -Wall -g -c Piece.cpp

Position.o:	Position.cpp Position.h ChessBoard.h
		g++ -Wall -g -c Position.cpp

Queen.o: Queen.cpp Piece.h ChessBoard.h Position.h Queen.h
		g++ -Wall -g -c Queen.cpp

Rook.o: Rook.cpp Piece.h ChessBoard.h Position.h Rook.h
		g++ -Wall -g -c Rook.cpp

clean:
		rm -f *.o execute
