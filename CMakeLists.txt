project(medes CXX)

set(MEDES_INCLUDE_DIRS
	include
	/usr/include
)

set(MEDES_LIBRARY_DIRS
	/usr/lib
)

set(MEDES_LIBRARIES
	libboost_filesystem.so
)

set(MEDES_SRC
	src/AppMain.cpp 
	src/Environment.cpp
	src/TargetHandler.cpp
	src/GeckoEmbed.cpp 
	src/config/ConfigContainer.cpp 
	src/config/ConfigIO.cpp 
	src/config/ConfigReader.cpp 
	src/config/ConfigWriter.cpp 
	src/rules/Rules.cpp 
	src/rules/LocalRules.cpp
	src/rules/RemoteRules.cpp
	src/rules/JavascriptRules.cpp
	src/gtk/AppWindow.cpp 
	src/gtk/MenuBar.cpp
	src/gtk/StatusBar.cpp
)

find_package(PkgConfig)
pkg_check_modules(GTK2 REQUIRED gtk+-2.0)
pkg_search_module(GTKMOZEMBED REQUIRED firefox-gtkmozembed xulrunner-gtkmozembed)
pkg_check_modules(XML2 REQUIRED libxml-2.0)

configure_file(
	${CMAKE_HOME_DIRECTORY}/include/Native.h.gen 
	${CMAKE_HOME_DIRECTORY}/include/Native.h
	ESCAPE_QUOTES
)

include_directories(
	${GTK2_INCLUDE_DIRS} 
	${GTKMOZEMBED_INCLUDE_DIRS} 
	${XML2_INCLUDE_DIRS} 
	${MEDES_INCLUDE_DIRS}
)

link_directories(
	${GTK2_LIBRARY_DIRS} 
	${GTKMOZEMBED_LIBRARY_DIRS} 
	${XML2_LIBRARY_DIRS}
	${MEDES_LIBRARY_DIRS}
)

add_executable(medes ${MEDES_SRC})

target_link_libraries(medes 
	${GTK2_LIBRARIES} 
	${GTKMOZEMBED_LIBRARIES} 
	${XML2_LIBRARIES}
	${MEDES_LIBRARIES}
)

set_target_properties(medes PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

install(DIRECTORY resources/share/ DESTINATION share/medes)
install(TARGETS medes RUNTIME DESTINATION bin)

