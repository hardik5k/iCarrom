cmake_minimum_required(VERSION 3.0.0)
project(iCarrom VERSION 0.1.0)


add_executable(iCarrom main.cpp)


target_link_libraries(iCarrom SDL2main SDL2 SDL2_image)

