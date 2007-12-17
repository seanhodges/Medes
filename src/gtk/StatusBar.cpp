#include <iostream>
	using std::cout;
	using std::endl;
#include "StatusBar.h"

/**
 * Create the status bar
 *
 * @param gecko - the running gecko engine instance
 */
StatusBar::StatusBar() {
	widget = gtk_statusbar_new();
	// Add the progress bar
	progressBar = gtk_progress_bar_new();
	gtk_box_pack_start(GTK_BOX(widget), progressBar, false, false, 0);
	cout << "added the status bar" << endl;
}

void StatusBar::setMessage(const string &message) {
	guint context = gtk_statusbar_get_context_id(GTK_STATUSBAR(widget), message.c_str());
	gtk_statusbar_push(GTK_STATUSBAR(widget), context, message.c_str());
}

void StatusBar::updateProgress(int current, int max) {
	if (current >= 0 && max >= current && max > 0) {
		double progress = (double)current / max;
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progressBar), progress);
	}
	else {
		// Resort to a pulse if progress is not known
		updateProgress();
	}
}

void StatusBar::updateProgress() {
	gtk_progress_bar_pulse(GTK_PROGRESS_BAR(progressBar));
}

void StatusBar::setProgressVisible(bool visible) {
	if (visible) gtk_widget_show(progressBar);
	else gtk_widget_hide(progressBar);
}
