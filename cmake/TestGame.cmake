project(CircusCharlieGame_Test)
set(PROJECT_NAME CircusCharlieGame_Test)
set(SOURCES
    test/test.cpp
    test/sdl_stub.cpp
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(SDL2_INCLUDE_DIR "${SDL2_SOURCE_DIR}/include")
set(SDL2_image_INCLUDE_DIR "${SDL2_image_SOURCE_DIR}/include")
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_image_INCLUDE_DIR})
add_executable(${PROJECT_NAME} ${SOURCES})

# SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications
if(TARGET SDL2::SDL2main)
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    message(VERBOSE "Target SDL2main ...")
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main)
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2-static SDL2_image::SDL2_image-static gtest_main)
