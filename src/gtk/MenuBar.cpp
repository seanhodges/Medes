#include <iostream>
	using std::cout;
	using std::endl;
#include "MenuBar.h"
#include "ConfigIO.h"

/**
 * Create the menu bar
 *
 * @param menuItems - items to be added to the menu
 */
MenuBar::MenuBar(vector<MenuElement> menuItems) {
	cout << "menu building started" << endl;
	menuWidget = gtk_menu_bar_new();
	// Create the menu items and groups
	for (vector<MenuElement>::iterator it = menuItems.end() - 1; it >= menuItems.begin(); it--) {
		MenuGroup* parentGroup = getMenuGroup(it->getGroup());
		MenuItem* newItem = new MenuItem(it->getLabel(), it->getTarget());
		parentGroup->addItem(it->getLabel(), newItem);
	}
	cout << "menu building complete" << endl;
}

/**
 * Delete containing menu groups when bar is destroyed
 */
MenuBar::~MenuBar() {
	for (map<string, MenuGroup*>::iterator it = groups.begin(); it != groups.end(); ++it) {
		delete (*it).second;
	}
	groups.clear();
}

/**
 * Retrieve or create a menu group
 *
 * @param label - the caption of the menu group to return
 *
 * @return the MenuGroup object matching the label
 */
MenuGroup* MenuBar::getMenuGroup(string label) {
	map<string, MenuGroup*>::iterator group = groups.find(label);
	if (group == groups.end()) {
		// Group does not exist, create it
		MenuGroup *newGroup = new MenuGroup(label);
		gtk_menu_bar_append(GTK_MENU_BAR(menuWidget), newGroup->getItemWidget());
		groups[label] = newGroup;
		group = groups.find(label);
		cout << "created menu group " << label << endl;
	}
	return group->second;
}

/**
 * Return the menu widget for the GTK window
 *
 * @return the finished widget object
 */
GtkWidget *MenuBar::getMenuWidget() {
	return menuWidget;
}

/**
 * Create a new menu group
 *
 * @param label - the caption for this group
 */
MenuGroup::MenuGroup(string label) {
	this->label = label;
	menuWidget = gtk_menu_new();
	itemWidget = gtk_menu_item_new_with_label(label.c_str());
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(itemWidget), menuWidget);
}

/**
 * Delete containing menu items when group is destroyed
 */
MenuGroup::~MenuGroup() {
	for (map<string, MenuItem*>::iterator it = items.begin(); it != items.end(); ++it) {
		delete (*it).second;
	}
	items.clear();
}

/**
 * Add a menu item to this group
 *
 * @param label - the caption for this item
 * @param item - the new MenuItem to add
 */
void MenuGroup::addItem(string label, MenuItem* item) {
	gtk_menu_shell_append(GTK_MENU_SHELL(menuWidget), item->getItemWidget());
	items.insert(std::make_pair(label, item));
}

/**
 * Get a menu item from this group
 *
 * @param label - the caption for this item
 */
MenuItem &MenuGroup::getItem(string label) {
	return *items[label];
}

/**
 * Create a new menu item
 *
 * @param label - the caption for this item
 * @param target - the target URL when activated
 */
MenuItem::MenuItem(const string& label, const string& target) {
	this->label = label;
	this->target = target;
	itemWidget = gtk_menu_item_new_with_label(label.c_str());
	setupCallbacks();
	cout << "\tcreated menu item " << label << endl;
}

/**
 * Set-up the callbacks for this menu item
 */
void MenuItem::setupCallbacks() {
	g_signal_connect(GTK_OBJECT(itemWidget), "activate", GTK_SIGNAL_FUNC(&MenuItem::eventClick), this);
}

/**
 * Callback event for menu items
 *
 * @param item - the widget that triggered the event
 * @param parent - the MenuItem object that triggered this event
 */
bool MenuItem::eventClick(GtkWidget *item, MenuItem *parent) {
	cout << "event from menu bar: " << ((MenuItem*)parent)->getLabel() << endl;
	return true;
}

