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

# Need to manually run moc due to using older Qt version,
# that is not properly integrated with system/CMake.
set(WINDOW_MOC_OUTPUT ${CMAKE_BINARY_DIR}/moc_mainWindow.cpp)
add_custom_command(
    OUTPUT ${WINDOW_MOC_OUTPUT}
    COMMAND $ENV{QTDIR}/bin/moc ${CMAKE_SOURCE_DIR}/app/mainWindow.hpp -o ${WINDOW_MOC_OUTPUT}
    DEPENDS ${CMAKE_SOURCE_DIR}/app/mainWindow.hpp
)

# Add the executable target
add_executable(editor app/raster_editor.cpp app/mainWindow.cpp ${WINDOW_MOC_OUTPUT})
# app/lcdrange.cpp app/cannon.cpp ${LCD_RANGE_MOC_OUTPUT} ${CANNON_MOC_OUTPUT})

# Include the Qt include paths
target_include_directories(editor PUBLIC $ENV{QTDIR}/include app)

# Link the Qt3 libraries to the executable
target_link_libraries(editor $ENV{QTDIR}/lib/libqt.so.3.3)
