MainWindow::MainWindow(ConfigContainer config) 
	: Gtk::Window() {

	setConfig(config);
	Gtk::VBox container;

	// Set-up window
	Geometry geom = config.getWindowGeom();
	move(geom.getLeft(), geom.getTop());
	resize(geom.getWidth(), geom.getHeight());
	set_title(config.getAppTitle());

	// Attach the menu bar
	container.pack_start(buildMenuBar());
	
	// Attach the Gecko engine
	gecko.init(config);
	container.pack_start(buildContent(gecko.getFrame()));

	this->add(container);
}

Gtk::Widget MainWindow::addMenuBar(Gtk::VBox &container) {
	Gtk::Widget menuBar = Gtk::ActionGroup::create();
	menuBar->add(Gtk::Action::create("MenuFile", "_File"));
	menuBar->add( Gtk::Action::create("New", Gtk::Stock::NEW), 
		sigc::mem_fun(*this, &ExampleWindow::on_action_file_new));
	return menuBar;
}

void MainWindow::addContent(GtkWindow *content) {
	Gtk::Widget content = Gtk::Widget.wrap(content);
	return content;
}

