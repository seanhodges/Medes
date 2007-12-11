#ifndef MENUBAR_DEFINED
#define MENUBAR_DEFINED

#include <gtk/gtk.h>
#include <string>
	using std::string;
#include <map>
	using std::map;
#include "ConfigContainer.h"
#include "GeckoEmbed.h"

class MenuItem {

	private:

		string label;
		string target;
		GtkWidget *itemWidget;
		GeckoEmbed *gecko;

	public:

		MenuItem() {}
		MenuItem(GeckoEmbed *gecko, const string& label, const string& target);

		GeckoEmbed *getGecko() { return gecko; }
		const string& getLabel() const { return label; }
		const string& getTarget() const { return target; }
		GtkWidget *getItemWidget() { return itemWidget; }

		void setAccelBinding(const string &code, GtkAccelGroup *globalAccel);

		void setupCallbacks();
		static bool eventClick(GtkWidget *item, MenuItem *parent);
};

class MenuGroup {

	private:

		string label;
		map<string, MenuItem*> items;
		GtkWidget *menuWidget;
		GtkWidget *itemWidget;

	public:

		MenuGroup() {}
		MenuGroup(const string& label);
        ~MenuGroup();

		void addItem(const string& label, MenuItem* item);
		MenuItem& getItem(const string& label);

		GtkWidget* getMenuWidget() { return menuWidget; }
		GtkWidget* getItemWidget() { return itemWidget; }
};

class MenuBar {

	private:

		GtkWidget *menuWidget;
		map<string, MenuGroup*> groups;
		MenuGroup testGroup;
		MenuItem testItem;

	public:

		MenuBar() {}
		MenuBar(vector<MenuElement> menuItems, GeckoEmbed *gecko, GtkAccelGroup *accelGroup);
		~MenuBar();

		MenuGroup *getMenuGroup(const string &label);
		GtkWidget *getMenuWidget();
};

#endif

