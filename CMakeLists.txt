cmake_minimum_required(VERSION 3.6.0)
cmake_policy(VERSION 3.6.0)

project(graphics)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_USE_STATIC_LIBS  ON)

add_subdirectory(opengl-base)
