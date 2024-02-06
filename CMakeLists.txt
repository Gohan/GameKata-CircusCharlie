cmake_minimum_required(VERSION 3.27)
# 隐式加载依赖的模块
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-read-modules-implicitly")
# cmake include Path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
# https://github.com/Kitware/CMake/blob/v3.27.8/Help/dev/experimental.rst
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API aa1f7df0-828a-4fcd-9afc-2dc80491aca7)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
include(Common)
include(BuildGame)
include(TestGame)
project(GameKata)

CPMUsePackageLock(package-lock.cmake)