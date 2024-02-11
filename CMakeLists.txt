cmake_minimum_required(VERSION 3.24)
project(tic VERSION 0.1.0 LANGUAGES CXX)

include(CTest)
enable_testing()

set(SOURCES TicTacToe.cpp TicTacToe.hpp main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# link libraries
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
# target_compile_features(tic PRIVATE cxx_std_17)