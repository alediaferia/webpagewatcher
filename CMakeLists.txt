cmake_minimum_required(VERSION 2.6)

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

######################### The Project ##################################
project (WebPageWatcher)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

set (WebPageWatcher_SRCS
main.cpp
mwindow.cpp
webview.cpp
selectionwidget.cpp
)

set (wpuis_UIS
    mwindowui.ui
    previewwidget.ui
)

include_directories(${CMAKE_CURRENT_BINARY_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR})

qt4_wrap_ui(WebPageWatcher_SRCS ${wpuis_UIS})
qt4_automoc(${WebPageWatcher_SRCS})

add_executable(wpwatcher ${WebPageWatcher_SRCS})
target_link_libraries(wpwatcher ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTWEBKIT_LIBRARY})

install( TARGETS wpwatcher RUNTIME DESTINATION bin)
