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

