include("${CMAKE_CURRENT_LIST_DIR}/CPM.cmake")

function(SetupGoogleTest)
    CPMAddPackage("gh:google/googletest#v1.14.0")
endfunction()

function(SetupSDL)
    set(SDL2IMAGE_INSTALL OFF)
    set(SDL_SHARED OFF)
    set(BUILD_SHARED_LIBS FALSE)

    CPMAddPackage("gh:libsdl-org/SDL#release-2.30.0")
    CPMAddPackage("gh:libsdl-org/SDL_image#release-2.8.2")
    set(SDL2_INCLUDE_DIR "${SDL2_SOURCE_DIR}/include" PARENT_SCOPE)
    set(SDL2_image_INCLUDE_DIR "${SDL2_image_SOURCE_DIR}/include" PARENT_SCOPE)
endfunction()

function(SetupFrameworks)
    CPMAddPackage("gh:microsoft/GSL#v4.0.0")
    set(GSL_INCLUDE_DIR "${GSL_SOURCE_DIR}/include" PARENT_SCOPE)
endfunction()

SetupFrameworks()
SetupGoogleTest()
SetupSDL()