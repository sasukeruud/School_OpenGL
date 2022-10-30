#include <iostream>
#include "go3D.h"

const char* title{ "go3D" };

int main(int argc, char** argv) {
	go3D app;

	app.ParseArguments(argc,argv);
	app.Init(title);
	return app.Run();
}