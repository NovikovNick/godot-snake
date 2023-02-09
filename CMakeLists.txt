cmake_minimum_required (VERSION 3.8)

project ("Snake")

set(CMAKE_CXX_STANDARD 20)

# Boost
set(BOOST_ROOT "C:\\local\\boost_1_80_0")
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
add_definitions( -DBOOST_ALL_NO_LIB )
add_definitions( -DBOOST_ALL_DYN_LINK )
   
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB GODOT_BIND "./src/*.h" "./src/*.cpp")
file(GLOB SNAKE_SRC "./src/model/*.h" "./src/model/*.cc")
file(GLOB UTIL "./src/util/*.h" "./src/util/*.cc")

include_directories(
	./src/
)

# Change the character set to unicode.
add_definitions(-D_UNICODE -DUNICODE)

# unit tests
add_executable(game_state_unit_test "test/game_state.cc" ${SNAKE_SRC} ${UTIL})
target_include_directories(game_state_unit_test PRIVATE Boost::unit_test_framework)

add_executable(grid_cell_unit_test "test/grid_cell.cc" ${SNAKE_SRC} ${UTIL})
target_include_directories(grid_cell_unit_test PRIVATE Boost::unit_test_framework)

