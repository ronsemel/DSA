cmake_minimum_required(VERSION 3.0.0)

#project(hw3 VERSION 0.1.0 LANGUAGES C++)
project(work VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)

set(MTM_FLAGS_DEBUG "-std=c++11 --pedantic-errors -Wall -Werror")
#set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")

set(CMAKE_C_FLAGS ${MTM_FLAGS_DEBUG})

#add_library(hw0-libraries /home/ronsemel/source/MTM/ex1/map.h /home/ronsemel/source/MTM/ex1/election.h)

#add_executable("${PROJECT_NAME}" /home/ronsemel/source/MTM/ex3/part_C/GameTest.cpp /home/ronsemel/source/MTM/ex3/part_C/Auxiliaries.cpp
#/home/ronsemel/source/MTM/ex3/part_C/Character.cpp /home/ronsemel/source/MTM/ex3/part_C/Soldier.cpp
#/home/ronsemel/source/MTM/ex3/part_C/Sniper.cpp /home/ronsemel/source/MTM/ex3/part_C/Medic.cpp
#/home/ronsemel/source/MTM/ex3/part_C/Game.cpp)

add_executable("${PROJECT_NAME}" /home/ronsemel/source/DSA/data_structures/graph.h)
