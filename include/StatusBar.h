#ifndef STATUSBAR_DEFINED
#define STATUSBAR_DEFINED

#include <gtk/gtk.h>
#include <string>
	using std::string;

class StatusBar {

	private:

		GtkWidget *widget;
		GtkWidget *progressBar;

	public:

		StatusBar();

		GtkWidget *getWidget() { return widget; }

		void setMessage(const string &message);
		void updateProgress(int current, int max);
		void updateProgress();
		void setProgressVisible(bool visible);
};

#endif

