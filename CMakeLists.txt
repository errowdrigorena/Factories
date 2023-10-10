cmake_minimum_required (VERSION 3.16)

include_directories(.)
#Version
SET(CMAKE_CXX_STANDARD 17)

project (DummyFactory)

add_executable(DummyFactory Main.cpp)
target_include_directories(DummyFactory PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/AuxiliaryClasses
    ${CMAKE_CURRENT_SOURCE_DIR}/CommonStrategies
    ${CMAKE_CURRENT_SOURCE_DIR}/TemplateStrategies)