function(EnsurePackage PackageName GitRepo GitTag)
    find_package(${PackageName} QUIET)
    if (NOT "${PackageName}_FOUND")
        include(FetchContent)
        FetchContent_Declare(
                ${PackageName}
                GIT_REPOSITORY ${GitRepo}
                GIT_TAG ${GitTag}
                GIT_SHALLOW TRUE
        )
        message("FetchContent_MakeAvailable: ${PackageName}")
        FetchContent_MakeAvailable(${PackageName})
    endif()
endfunction()

function(SetupGoogleTest)
    EnsurePackage(googletest https://github.com/google/googletest.git v1.14.0)
endfunction()

function(SetupSDL)
    EnsurePackage(SDL2 https://github.com/libsdl-org/SDL release-2.30.0)
    set(SDL2_INCLUDE_DIR "${SDL2_SOURCE_DIR}/include" PARENT_SCOPE)

    EnsurePackage(SDL2_image https://github.com/libsdl-org/SDL_image release-2.8.2)
    set(SDL2_image_INCLUDE_DIR "${SDL2_image_SOURCE_DIR}/include" PARENT_SCOPE)
endfunction()

function(SetupFrameworks)
    EnsurePackage(GSL https://github.com/microsoft/GSL v4.0.0)
    set(GSL_INCLUDE_DIR "${GSL_SOURCE_DIR}/include" PARENT_SCOPE)

    set(BOOST_INCLUDE_LIBRARIES thread filesystem system)
    set(BOOST_ENABLE_CMAKE ON)
    EnsurePackage(Boost https://github.com/boostorg/boost.git boost-1.84.0)
endfunction()

SetupFrameworks()
SetupGoogleTest()
SetupSDL()