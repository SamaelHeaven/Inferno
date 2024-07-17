cmake_minimum_required(VERSION 3.5.0)
project(inferno)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(RAYLIB_VERSION 5.0)
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif ()
endif ()

set(BOX2D_VERSION 2.4.1)
find_package(box2d QUIET)
if (NOT box2d_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            box2d
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/erincatto/box2d/archive/refs/tags/v${BOX2D_VERSION}.tar.gz
    )
    FetchContent_GetProperties(box2d)
    if (NOT box2d_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(box2d)
        set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
        set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE)
        add_subdirectory(${box2d_SOURCE_DIR} ${box2d_BINARY_DIR})
    endif ()
endif ()

set(PUGIXML_VERSION 1.14)
find_package(pugixml QUIET)
if (NOT pugixml_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            pugixml
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/zeux/pugixml/releases/download/v${PUGIXML_VERSION}/pugixml-${PUGIXML_VERSION}.tar.gz
    )
    FetchContent_GetProperties(pugixml)
    if (NOT pugixml_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(pugixml)
        add_subdirectory(${pugixml_SOURCE_DIR} ${pugixml_BINARY_DIR})
    endif ()
endif ()

set(MAGIC_ENUM_VERSION 0.9.6)
find_package(magic_enum QUIET)
if (NOT magic_enum_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            magic_enum
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/Neargye/magic_enum/releases/download/v${MAGIC_ENUM_VERSION}/magic_enum-v${MAGIC_ENUM_VERSION}.tar.gz
    )
    FetchContent_GetProperties(magic_enum)
    if (NOT magic_enum_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(magic_enum)
        add_subdirectory(${magic_enum_SOURCE_DIR} ${magic_enum_BINARY_DIR})
    endif ()
endif ()

add_library(${PROJECT_NAME}
        src/inferno.cpp
        src/inferno.h
        src/include/inferno.h
        src/include/inferno-core.h
        src/include/inferno-input.h
        src/include/inferno-drawing.h
        src/include/inferno-math.h
        src/core/Platform.cpp
        src/core/Platform.h
        src/core/file.cpp
        src/core/file.h
        src/core/GameConfig.cpp
        src/core/GameConfig.h
        src/core/Game.cpp
        src/core/Game.h
        src/core/Scene.cpp
        src/core/Scene.h
        src/core/Time.cpp
        src/core/Time.h
        src/core/Renderer.cpp
        src/core/Renderer.h
        src/input/Key.h
        src/input/Keyboard.cpp
        src/input/Keyboard.h
        src/input/MouseButton.h
        src/input/Mouse.cpp
        src/input/Mouse.h
        src/drawing/Color.cpp
        src/drawing/Color.h
        src/math/Vector2.cpp
        src/math/Vector2.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    PUBLIC_HEADER "src/include"
)

target_include_directories(${PROJECT_NAME} PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/include>
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include>
)

target_link_libraries(${PROJECT_NAME} PUBLIC raylib box2d pugixml magic_enum)