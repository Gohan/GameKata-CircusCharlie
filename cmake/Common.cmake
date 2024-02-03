function(EnsurePackage PackageName GitRepo GitTag)
    find_package(${PackageName} QUIET)
    if (NOT "${PackageName}_FOUND")
        include(FetchContent)
        FetchContent_Declare(
                ${PackageName}
                GIT_REPOSITORY ${GitRepo}
                GIT_TAG ${GitTag}
        )
        message("FetchContent_MakeAvailable: ${PackageName}")
        FetchContent_MakeAvailable(${PackageName})
    endif()
endfunction()

EnsurePackage(raylib https://github.com/raysan5/raylib.git 5.0)
EnsurePackage(raylib_cpp https://github.com/RobLoach/raylib-cpp.git v5.0.0)
EnsurePackage(googletest https://github.com/google/googletest.git v1.14.0)
EnsurePackage(SDL2 https://github.com/libsdl-org/SDL release-2.30.0)
EnsurePackage(SDL2_image https://github.com/libsdl-org/SDL_image release-2.8.2)
