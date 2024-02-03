cmake_minimum_required(VERSION 3.27)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Common.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/BuildGame.cmake)

project(GameKata_CircusCharlie)
set(PROJECT_NAME GameKata_CircusCharlie)
set(SOURCES src/main2.cpp)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

EnsurePackage(raylib https://github.com/raysan5/raylib.git 5.0)
EnsurePackage(raylib_cpp https://github.com/RobLoach/raylib-cpp.git v5.0.0)
EnsurePackage(googletest https://github.com/google/googletest.git v1.14.0)
EnsurePackage(SDL2 https://github.com/libsdl-org/SDL release-2.30.0)
EnsurePackage(SDL2_image https://github.com/libsdl-org/SDL_image release-2.8.2)

## raylib
#find_package(raylib QUIET)
#if (NOT raylib_FOUND)
#    include(FetchContent)
#    FetchContent_Declare(
#            raylib
#            GIT_REPOSITORY https://github.com/raysan5/raylib.git
#            GIT_TAG 5.0
#    )
#    FetchContent_MakeAvailable(raylib)
#endif()

## raylib-cpp
#find_package(raylib_cpp QUIET)
#if (NOT raylib_cpp_FOUND)
#    include(FetchContent)
#    FetchContent_Declare(
#            raylib_cpp
#            GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
#            GIT_TAG v5.0.0
#    )
#    FetchContent_MakeAvailable(raylib_cpp)
#endif()

# googletest
#find_package(googletest QUIET)
#if (NOT googletest_FOUND)
#    include(FetchContent)
#    FetchContent_Declare(
#            googletest
#            URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
#    )
#    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#    FetchContent_MakeAvailable(googletest)
#endif()

## sdl2
#find_package(SDL2 QUIET)
#if (NOT SDL2_FOUND)
#    include(FetchContent)
#    FetchContent_Declare(
#            SDL2
#            GIT_REPOSITORY  https://github.com/libsdl-org/SDL
#            GIT_TAG         release-2.30.0
#            GIT_PROGRESS    TRUE
#    )
#    FetchContent_MakeAvailable(SDL2)
#endif()
#
## sdl2 image
#find_package(SDL2_image QUIET)
#if (NOT SDL2_image_FOUND)
#    include(FetchContent)
#    FetchContent_Declare(
#            SDL2_image
#            GIT_REPOSITORY  https://github.com/libsdl-org/SDL_image
#            GIT_TAG         release-2.8.2
#            GIT_PROGRESS    TRUE
#    )
#    FetchContent_MakeAvailable(SDL2_image)
#endif()

set(SDL2_INCLUDE_DIR "${SDL2_SOURCE_DIR}/include")
set(SDL2_image_INCLUDE_DIR "${SDL2_image_SOURCE_DIR}/include")
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_image_INCLUDE_DIR})
message("Hello ${SDL2_INCLUDE_DIR} ${SDL2_SOURCE_DIR} ${SDL2_image_SOURCE_DIR}")
add_executable(${PROJECT_NAME} ${SOURCES})

# SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications
if(TARGET SDL2::SDL2main)
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main)
endif()
# Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library, SDL2::SDL2-static is the static SDL libarary.
# target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::image)
# target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image::SDL2_image)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2-static)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image::SDL2_image-static)
target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib_cpp)
#target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib_cpp gtest_main)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")

    # Required linker flags for using Raylib with Emscripten
    target_link_options(${PROJECT_NAME} PRIVATE -sEXPORTED_FUNCTIONS=['_main','_malloc'] -sEXPORTED_RUNTIME_METHODS=ccall -sUSE_GLFW=3)
endif()
