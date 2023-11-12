cmake_minimum_required(VERSION 3.24)
project(AnimeCode)

set(CMAKE_CXX_STANDARD 17)

add_executable(AnimeCode main.cpp
        ReadData.cpp
        Anime.cpp)
