
cmake_minimum_required(VERSION 3.0)

macro(ADD_OSX_FRAMEWORK fwname target)
    find_library(FRAMEWORK_${fwname}
    NAMES ${fwname}
    PATHS ${CMAKE_OSX_SYSROOT}/System/Library
    PATH_SUFFIXES Frameworks
    NO_DEFAULT_PATH)
    if( ${FRAMEWORK_${fwname}} STREQUAL FRAMEWORK_${fwname}-NOTFOUND)
        MESSAGE(ERROR ": Framework ${fwname} not found")
    else()
        TARGET_LINK_LIBRARIES(${target} PUBLIC "${FRAMEWORK_${fwname}}")
        MESSAGE(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}")
    endif()
endmacro(ADD_OSX_FRAMEWORK)

#Force C++11 on mac
set(CMAKE_CXX_FLAGS "-std=c++11")

# Name of the project (will be the name of the plugin)
project(opengl-context)

file(GLOB SOURCE_FILES "src/*.cc" "src/*.h" "src/**/*.cc" "src/**/*.h")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

ADD_OSX_FRAMEWORK(OpenGL ${PROJECT_NAME})
SET(CMAKE_EXE_LINKER_FLAGS "-bind_at_load -framework OpenGL -w")


# ---------------------------------------------------------------------
#             START OF NODE-SPECIFIC BUILD
# ---------------------------------------------------------------------


# Gives our library file a .node extension without any "lib" prefix
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

# Include N-API wrappers
execute_process(COMMAND /usr/local/bin/node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )

string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})

# Essential include files to build a node addon,
# You should add this line in every CMake.js based project
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_JS_INC})

# Essential library files to link to a node addon
# You should add this line in every CMake.js based project
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})
