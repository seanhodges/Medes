project(medes)

set(MEDES_INCLUDE_DIRS
	include
)

set(MEDES_SRC
	src/AppMain.cpp 
	src/AppWindow.cpp 
	src/ConfigContainer.cpp 
	src/ConfigReader.cpp 
	src/GeckoEmbed.cpp 
	src/rules/Handler.cpp 
	src/rules/DomainHandler.cpp
)

find_package(PkgConfig)
pkg_check_modules(GTK2 REQUIRED gtk+-2.0)
pkg_check_modules(GTKMOZEMBED REQUIRED firefox-gtkmozembed)
pkg_check_modules(XML2 REQUIRED libxml-2.0)

include_directories(${GTK2_INCLUDE_DIRS})
include_directories(${GTKMOZEMBED_INCLUDE_DIRS})
include_directories(${XML2_INCLUDE_DIRS})
include_directories(${MEDES_INCLUDE_DIRS})

link_directories(${GTK2_LIBRARY_DIRS})
link_directories(${GTKMOZEMBED_LIBRARY_DIRS})
link_directories(${XML2_LIBRARY_DIRS})

add_executable(medes ${MEDES_SRC})

target_link_libraries(medes ${GTK2_LIBRARIES})
target_link_libraries(medes ${GTKMOZEMBED_LIBRARIES})
target_link_libraries(medes ${XML2_LIBRARIES})

install(TARGETS medes RUNTIME DESTINATION bin)

