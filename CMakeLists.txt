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
	src/AppWindow.cpp 
	src/Environment.cpp
	src/GeckoEmbed.cpp 
	src/config/ConfigContainer.cpp 
	src/config/ConfigIO.cpp 
	src/config/ConfigReader.cpp 
	src/config/ConfigWriter.cpp 
	src/rules/Handler.cpp 
	src/rules/DomainHandler.cpp
)

find_package(PkgConfig)
pkg_check_modules(GTK2 REQUIRED gtk+-2.0)
pkg_check_modules(GTKMOZEMBED REQUIRED firefox-gtkmozembed)
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
install(DIRECTORY resources/desktop/ DESTINATION share/applications)
install(DIRECTORY resources/pixmaps/ DESTINATION share/pixmaps)
install(TARGETS medes RUNTIME DESTINATION bin)

