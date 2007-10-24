project(medes)

find_package(PkgConfig)
pkg_check_modules(GTK2 REQUIRED gtk+-2.0)
pkg_check_modules(GTKMOZEMBED REQUIRED firefox-gtkmozembed)
pkg_check_modules(XML2 REQUIRED libxml-2.0)

include_directories(${GTK2_INCLUDE_DIRS})
include_directories(${GTKMOZEMBED_INCLUDE_DIRS})
include_directories(${XML2_INCLUDE_DIRS})
include_directories(include)

link_directories(${GTK2_LIBRARY_DIRS})
link_directories(${GTKMOZEMBED_LIBRARY_DIRS})
link_directories(${XML2_LIBRARY_DIRS})
link_libraries(${GTK2_LIBRARIES})
link_libraries(${GTKMOZEMBED_LIBRARIES})
link_libraries(${XML2_LIBRARIES})

add_executable(medes src/AppMain.cpp src/AppWindow.cpp src/ConfigContainer.cpp src/ConfigReader.cpp src/GeckoEmbed.cpp)

