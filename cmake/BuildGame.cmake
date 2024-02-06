project(CircusCharlieGame)
set(PROJECT_NAME CircusCharlieGame)
file(GLOB_RECURSE CircusCharlieGame_MODULES src/*.cppm src/*.ixx)
file(GLOB_RECURSE CircusCharlieGame_SOURCES src/*.cpp src/*.cxx)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(PLATFORM "Win32")

set(CircusCharlieGame_INCLUDE_DIR "src")
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_image_INCLUDE_DIR} ${GSL_INCLUDE_DIR})
message("Hello ${SDL2_INCLUDE_DIR} ${SDL2_SOURCE_DIR} ${SDL2_image_SOURCE_DIR}")
#add_executable(${PROJECT_NAME} ${CircusCharlieGame_SOURCES})
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
        PUBLIC
        FILE_SET all_my_modules TYPE CXX_MODULES FILES ${CircusCharlieGame_MODULES}
        PRIVATE
        ${CircusCharlieGame_SOURCES}
)

# SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications
if(TARGET SDL2::SDL2main)
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    message(VERBOSE "Target SDL2main ...")
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main)
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2-static)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image::SDL2_image-static)
#target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib_cpp)
#target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib_cpp gtest_main)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")

    # Required linker flags for using Raylib with Emscripten
    target_link_options(${PROJECT_NAME} PRIVATE -sEXPORTED_FUNCTIONS=['_main','_malloc'] -sEXPORTED_RUNTIME_METHODS=ccall -sUSE_GLFW=3)
endif()
