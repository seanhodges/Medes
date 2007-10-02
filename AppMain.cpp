
#include "AppWindow.cpp"
#include "GeckoEmbed.cpp"

int main(int argc, char *argv[]) {

	// Create the application window
	AppWindow appWindow(argc, argv);
    
	// Attach the embedded browser
	GeckoEmbed gecko;
	gecko.setUrl("http://maps.google.co.uk");
	appWindow.attachBrowser(gecko.getFrame());

    // Show the window
	appWindow.show();
	gecko.bringUp();
	appWindow.start();

	// Shut down gracefully
	gecko.tearDown();

    return 0;
}

