cmake_minimum_required(VERSION 3.5.0)
project(game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET)
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
find_package(box2d ${BOX2D_VERSION} QUIET)
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
find_package(pugixml ${PUGIXML_VERSION} QUIET)
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
find_package(magic_enum ${MAGIC_ENUM_VERSION} QUIET)
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

add_executable(${PROJECT_NAME}
        game/src/game.cpp
        game/src/game.h
        game/src/scenes/MainScene.cpp
        game/src/scenes/MainScene.h
        inferno/src/inferno.cpp
        inferno/src/inferno.h
        inferno/src/include/inferno.h
        inferno/src/include/core.h
        inferno/src/include/input.h
        inferno/src/include/drawing.h
        inferno/src/core/Platform.cpp
        inferno/src/core/Platform.h
        inferno/src/core/file.cpp
        inferno/src/core/file.h
        inferno/src/core/GameConfig.cpp
        inferno/src/core/GameConfig.h
        inferno/src/core/Game.cpp
        inferno/src/core/Game.h
        inferno/src/core/Scene.cpp
        inferno/src/core/Scene.h
        inferno/src/core/Time.cpp
        inferno/src/core/Time.h
        inferno/src/core/Renderer.cpp
        inferno/src/core/Renderer.h
        inferno/src/input/Key.h
        inferno/src/input/Keyboard.cpp
        inferno/src/input/Keyboard.h
        inferno/src/input/MouseButton.h
        inferno/src/input/Mouse.cpp
        inferno/src/input/Mouse.h
        inferno/src/drawing/Color.cpp
        inferno/src/drawing/Color.h
)

target_link_libraries(${PROJECT_NAME} PUBLIC raylib box2d pugixml magic_enum)
target_include_directories(${PROJECT_NAME} PUBLIC SYSTEM ${PROJECT_SOURCE_DIR}/inferno/src/include)

if (${PLATFORM} STREQUAL "Desktop")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -s -mwindows")
endif ()

if (EMSCRIPTEN)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --preload-file ${PROJECT_SOURCE_DIR}/game/assets@/assets")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
else ()
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_SOURCE_DIR}/game/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
    )
endif ()

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif ()