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
void MenuBar::init(vector<MenuElement> menuItems) {
	cout << "menu building started" << endl;
	menuWidget = gtk_menu_bar_new();
	// Create the menu items
	for (vector<MenuElement>::iterator it = menuItems.end() - 1; it >= menuItems.begin(); it--) {
		MenuGroup parentGroup = getMenuGroup(it->getGroup());
		MenuItem newItem(it->getLabel(), it->getTarget());
		gtk_menu_shell_append(GTK_MENU_SHELL(parentGroup.getMenuWidget()), newItem.getItemWidget());
		parentGroup.addItem(it->getLabel(), newItem);
	}
	cout << "menu building complete" << endl;
}

/**
 * Retrieve or create a menu group
 *
 * @param label - the caption of the menu group to return
 *
 * @return the MenuGroup object matching the label
 */
MenuGroup& MenuBar::getMenuGroup(string label) {
	map<string, MenuGroup>::iterator group = groups.find(label);
	if (group == groups.end()) {
		// Group does not exist, create it
		MenuGroup newGroup(label);
		gtk_menu_bar_append(GTK_MENU_BAR(menuWidget), newGroup.getItemWidget());
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
 * Add a menu item to this group
 *
 * @param label - the caption for this item
 * @param item - the new MenuItem to add
 */
void MenuGroup::addItem(string label, MenuItem item) {
	items[label] = item;
}

/**
 * Create a new menu item
 *
 * @param label - the caption for this item
 * @param target - the target URL when activated
 */
MenuItem::MenuItem(string label, string target) {
	this->label = label;
	this->target = target;
	itemWidget = gtk_menu_item_new_with_label(label.c_str());
	// Attach the callback
	gtk_signal_connect(GTK_OBJECT(itemWidget), "activate", GTK_SIGNAL_FUNC(&MenuItem::eventClick), this);
	cout << "\tcreated menu item " << label << endl;
}

/**
 * Callback event for menu items
 *
 * @param item - the widget that triggered the event
 * @param event - the event that occured
 * @param parent - the MenuItem object that triggered this event
 */
bool MenuItem::eventClick(GtkWidget *item, GdkEvent *event, MenuItem& parent) {
	cout << "event from menu bar: " << parent.getTarget() << endl;
}

