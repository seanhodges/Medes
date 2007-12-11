#include <iostream>
	using std::cout;
	using std::endl;
#include <boost/algorithm/string.hpp>
	using boost::algorithm::split;
	using boost::algorithm::is_any_of;
#include <vector>
	using std::vector;
#include "MenuBar.h"
#include "ConfigIO.h"
#include "TargetHandler.h"

/**
 * Create the menu bar
 *
 * @param menuItems - items to be added to the menu
 * @param gecko - the running gecko engine instance
 */
MenuBar::MenuBar(vector<MenuElement> menuItems, GeckoEmbed *gecko, GtkAccelGroup *accelGroup) {
	cout << "menu building started" << endl;
	menuWidget = gtk_menu_bar_new();
	// Create the menu items and groups
	for (vector<MenuElement>::iterator it = menuItems.end() - 1; it >= menuItems.begin(); it--) {
		MenuGroup* parentGroup = getMenuGroup(it->getGroup());
		if (it->isSeparator()) {
			parentGroup->addSeparator();
		}
		else {
			MenuItem* newItem = new MenuItem(gecko, it->getLabel(), it->getTarget());
			if (it->getAccel() != "") newItem->setAccelBinding(it->getAccel(), accelGroup);
			parentGroup->addItem(it->getLabel(), newItem);
		}
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
MenuGroup* MenuBar::getMenuGroup(const string& label) {
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
MenuGroup::MenuGroup(const string &label) {
	this->label = label;
	menuWidget = gtk_menu_new();
	itemWidget = gtk_menu_item_new_with_mnemonic(label.c_str());
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
void MenuGroup::addItem(const string &label, MenuItem* item) {
	gtk_menu_shell_append(GTK_MENU_SHELL(menuWidget), item->getItemWidget());
	items.insert(std::make_pair(label, item));
}

/**
 * Add a menu separator to this group
 */
void MenuGroup::addSeparator() {
	GtkWidget *separator = gtk_separator_menu_item_new();
	gtk_container_add(GTK_CONTAINER(menuWidget), separator);
}

/**
 * Get a menu item from this group
 *
 * @param label - the caption for this item
 */
MenuItem &MenuGroup::getItem(const string &label) {
	return *items[label];
}

/**
 * Create a new menu item
 *
 * @param gecko - the running gecko engine instance
 * @param label - the caption for this item
 * @param target - the target URL when activated
 */
MenuItem::MenuItem(GeckoEmbed *gecko, const string& label, const string& target) {
	this->gecko = gecko;
	this->label = label;
	this->target = target;
	itemWidget = gtk_menu_item_new_with_mnemonic(label.c_str());
	setupCallbacks();
	cout << "created menu item " << label << endl;
}

/**
 * Bind a new keyboard accelerator to this item
 */
void MenuItem::setAccelBinding(const string &code, GtkAccelGroup *globalAccel) {
	int mods = 0;
	bool invalid = false;
	char key = 0;
	// Resolve the key code
	vector<string> codeParts;
	split(codeParts, code, is_any_of("+"));
	for (vector<string>::iterator it = codeParts.begin(); it != codeParts.end(); it++) {
		if (*it == "ctrl") mods += 1;
		else if (*it == "alt") mods += 2;
		else if (*it == "shift") mods += 4;
		else if (it->length() == 1) key = (char)*it->c_str();
		else invalid = true; // Disallow binding if code is invalid
	}
	if (key > 0 && invalid == false && mods > 0) {
		// Couldn't seem to store the masks, so this is the hacky alternative
		if (mods == 1) 
			gtk_widget_add_accelerator(itemWidget, "activate", globalAccel, key, (GdkModifierType)(GDK_CONTROL_MASK), GTK_ACCEL_VISIBLE);
		else if (mods == 2)
			gtk_widget_add_accelerator(itemWidget, "activate", globalAccel, key, (GdkModifierType)(GDK_MOD1_MASK), GTK_ACCEL_VISIBLE);
		else if (mods == 3)
			gtk_widget_add_accelerator(itemWidget, "activate", globalAccel, key, (GdkModifierType)(GDK_CONTROL_MASK | GDK_MOD1_MASK), GTK_ACCEL_VISIBLE);
		else if (mods == 4)
			gtk_widget_add_accelerator(itemWidget, "activate", globalAccel, key, (GdkModifierType)(GDK_SHIFT_MASK), GTK_ACCEL_VISIBLE);
		else if (mods == 5)
			gtk_widget_add_accelerator(itemWidget, "activate", globalAccel, key, (GdkModifierType)(GDK_CONTROL_MASK | GDK_SHIFT_MASK), GTK_ACCEL_VISIBLE);
		else if (mods == 6)
			gtk_widget_add_accelerator(itemWidget, "activate", globalAccel, key, (GdkModifierType)(GDK_MOD1_MASK | GDK_SHIFT_MASK), GTK_ACCEL_VISIBLE);
		else if (mods == 7)
			gtk_widget_add_accelerator(itemWidget, "activate", globalAccel, key, (GdkModifierType)(GDK_CONTROL_MASK | GDK_MOD1_MASK | GDK_SHIFT_MASK), GTK_ACCEL_VISIBLE);
		cout << "bound menu item " << label << " to code " << code << endl;
	}
	else {
		cout << "failed to bind menu item " << label << ", key code is invalid" << endl;
	}
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
 *
 * @return always true
 */
bool MenuItem::eventClick(GtkWidget *item, MenuItem *parent) {
	GeckoEmbed *gecko = ((MenuItem*)parent)->getGecko();
	string label = ((MenuItem*)parent)->getLabel(); 
	string target = ((MenuItem*)parent)->getTarget(); 
	cout << "event from menu bar: item=" << label << "; target=" << target << endl;
	// Send the target to the handler
	TargetHandler handler(target, gecko);
	handler.runAction();
	return true;
}

