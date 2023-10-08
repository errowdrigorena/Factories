cmake_minimum_required (VERSION 3.0)

include_directories(.)
#Version
SET(CMAKE_CXX_STANDARD 17)

include_directories(${Boost_INCLUDE_DIRS}, 
    ${CMAKE_CURRENT_SOURCE_DIR}/../AuxiliaryClasses,
    ${CMAKE_CURRENT_SOURCE_DIR}/../CommonStrategies)

project (DummyFactory)

add_executable(DummyFactory Main.cpp)
