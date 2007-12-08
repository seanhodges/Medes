#ifndef MENUBAR_DEFINED
#define MENUBAR_DEFINED

#include <gtk/gtk.h>
#include <string>
	using std::string;
#include <map>
	using std::map;
#include "ConfigContainer.h"

class MenuItem {

	private:

		string label;
		string target;
		GtkWidget *itemWidget;

	public:

		MenuItem() {}
		MenuItem(const string& label, const string& target);

		const string& getLabel() const { return label; }
		const string& getTarget() const { return target; }
		GtkWidget *getItemWidget() { return itemWidget; }

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
		MenuGroup(string label);
        ~MenuGroup();

		void addItem(string label, MenuItem* item);
		MenuItem& getItem(string label);

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

		void init(vector<MenuElement> menuItems);
		MenuGroup *getMenuGroup(string label);
		GtkWidget *getMenuWidget();

		static bool testEvent(GtkWidget *item, MenuItem *testItem);
};

#endif

