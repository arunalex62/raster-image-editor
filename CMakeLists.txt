cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

# Define the project name
project(raster_editor LANGUAGES CXX)

# Add warnings when compiling/building executable.
# Additionally, ignore deprecated-copy warnings due to older Qt version.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-deprecated-copy")

# Check if system has QTDIR defined before progressing.
if(NOT DEFINED ENV{QTDIR})
    message(FATAL_ERROR "QTDIR environment variable is not set.
     Please make sure Qt is installed on your system in order
     to build the program.")
endif()

# Need to manually run moc due to using older Qt version
# that is not properly integrated with system/CMake.
# Used a comment on this StackOverflow post to learn how to do this:
# https://stackoverflow.com/questions/45994432/how-to-generate-moc-cpp-files-using-cmake
set(WINDOW_MOC_OUTPUT ${CMAKE_BINARY_DIR}/moc_mainWindow.cpp)
add_custom_command(
    OUTPUT ${WINDOW_MOC_OUTPUT}
    COMMAND $ENV{QTDIR}/bin/moc ${CMAKE_SOURCE_DIR}/include/mainWindow.hpp -o ${WINDOW_MOC_OUTPUT}
    DEPENDS ${CMAKE_SOURCE_DIR}/include/mainWindow.hpp
)

set(IMAGE_MOC_OUTPUT ${CMAKE_BINARY_DIR}/moc_imageView.cpp)
add_custom_command(
    OUTPUT ${IMAGE_MOC_OUTPUT}
    COMMAND $ENV{QTDIR}/bin/moc ${CMAKE_SOURCE_DIR}/include/imageView.hpp -o ${IMAGE_MOC_OUTPUT}
    DEPENDS ${CMAKE_SOURCE_DIR}/include/imageView.hpp
)

set(BRUSHSIZEDIALOG_MOC_OUTPUT ${CMAKE_BINARY_DIR}/moc_brushSizeDialogWidget.cpp)
add_custom_command(
    OUTPUT ${BRUSHSIZEDIALOG_MOC_OUTPUT}
    COMMAND $ENV{QTDIR}/bin/moc ${CMAKE_SOURCE_DIR}/include/brushSizeDialogWidget.hpp
     -o ${BRUSHSIZEDIALOG_MOC_OUTPUT}
    DEPENDS ${CMAKE_SOURCE_DIR}/include/brushSizeDialogWidget.hpp
)

# Add the executable with its necessary source/header files.
add_executable(editor app/raster_editor.cpp app/mainWindow.cpp app/menuBar.cpp
app/statusBar.cpp app/fileIO.cpp app/imageView.cpp app/brushSizeDialogWidget.cpp 
app/resizeCanvasDialogWidget.cpp app/newImageDialogWidget.cpp
 ${WINDOW_MOC_OUTPUT} ${IMAGE_MOC_OUTPUT} ${BRUSHSIZEDIALOG_MOC_OUTPUT})

# Include the Qt include and include/ folder.
target_include_directories(editor PUBLIC $ENV{QTDIR}/include include)

# Link the Qt libraries to the executable
target_link_libraries(editor $ENV{QTDIR}/lib/libqt-mt.so.3.3)

# Install the editor program into the bin directory.
install(TARGETS editor DESTINATION bin)

# Install the demo program into the bin directory.
install(PROGRAMS demo DESTINATION bin)