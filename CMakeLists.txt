project (Medes)

include (${CMAKE_ROOT}/Modules/FindGTK.cmake)
if (GTK_FOUND)
	include_directories(${GTK_INCLUDE_DIR})
	link_libraries(${GTK_LIBRARIES})
else (GTK_FOUND)
	message(FATAL_ERROR
		"Program requires GTK source (apt-get install libgtk-dev)")
endif (GTK_FOUND)

include_directories(/usr/include/libxml2)
include_directories(/usr/include/firefox)
include_directories(/usr/include/firefox/gtkembedmoz)

link_libraries(/usr/lib/libxml2)
link_libraries(/usr/lib/firefox/libgtkembedmoz)

include_directories(include)

add_executable (medes src/AppMain.cpp src/AppWindow.cpp src/ConfigContainer.cpp src/ConfigReader.cpp src/GeckoEmbed.cpp)
