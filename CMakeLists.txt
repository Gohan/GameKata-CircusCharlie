cmake_minimum_required(VERSION 3.27)
set(CMAKE_VERBOSE_MAKEFILE ON)
# https://github.com/Kitware/CMake/blob/v3.27.8/Help/dev/experimental.rst
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API aa1f7df0-828a-4fcd-9afc-2dc80491aca7)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Common.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/BuildGame.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/TestGame.cmake)
project(GameKata)

CPMUsePackageLock(package-lock.cmake)