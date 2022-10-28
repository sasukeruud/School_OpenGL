#include <iostream>
#include "chessBoard.h"

const char* title{ "ChessBoard" };

int main(int argc, char** argv) {
	chessBoard app;

	app.ParseArguments(argc,argv);
	app.Init(title);
	return app.Run();
}