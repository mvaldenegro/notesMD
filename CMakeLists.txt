project(notesmd)
find_package(KDE4 REQUIRED)
include (KDE4Defaults)

include_directories(${KDE4_INCLUDES})
include_directories(src)

set ( CMAKE_CXX_FLAGS "-Wall -pedantic -Wno-long-long -std=c++11")

file(GLOB notesmd_SOURCES src/*.cpp src/*/*.cpp src/*/*/*.cpp)

kde4_add_ui_files(notesmd_SOURCES src/ui/CreateNotebookDialog.ui)

set(QT_USE_QTWEBKIT true)
INCLUDE(${QT_USE_FILE}) 

kde4_add_executable(notesmd ${notesmd_SOURCES})
target_link_libraries(notesmd ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} ${QT_LIBRARIES})

install(TARGETS notesmd ${INSTALL_TARGETS_DEFAULT_ARGS})
