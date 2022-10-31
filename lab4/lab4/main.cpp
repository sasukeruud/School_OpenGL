#include <iostream>
#include "lab4.h"

const char* title{ "lab4" };

int main(int argc, char** argv) {
	lab4 app;

	app.ParseArguments(argc,argv);
	app.Init(title);
	return app.Run();
}