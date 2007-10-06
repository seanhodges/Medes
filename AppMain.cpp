
#include "AppWindow.h"

int main(int argc, char* argv[]) {

	// Create the application window
	AppWindow appWindow(argc, argv);
	appWindow.show();
	appWindow.start();

    return 0;
}

