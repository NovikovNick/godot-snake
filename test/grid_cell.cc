#define BOOST_TEST_MODULE SolutionTest
#define CASE_1 1
#define CASE_2 1
#define CASE_3 1
#define CASE_4 1
#define CASE_5 1
#define DEBUG 1

#include "../src/model/grid_cell.h"

#include <bitset>
#include <boost/test/included/unit_test.hpp>
#include <iostream>

#if CASE_1
BOOST_AUTO_TEST_CASE(case1) {
  // arrange
  using namespace snake;
  
  // act 
  GridCell cell;
  
  // assert
  BOOST_CHECK(BOARD_CELL_TYPE::EMPTY == cell.type);
}
#endif  // !CASE_1

#if CASE_2
BOOST_AUTO_TEST_CASE(case2) {
  // arrange
  using namespace snake;
  snake::GridCell cell;

  // act 
  cell.setPlayer(0, Direction::LEFT, Direction::LEFT);

  //assert
  BOOST_CHECK(BOARD_CELL_TYPE::PLAYER == cell.type);
  BOOST_CHECK_EQUAL(0, cell.player_id);
  BOOST_CHECK(snake::Direction::LEFT == cell.next);
  BOOST_CHECK(snake::Direction::LEFT == cell.prev);
}
#endif  // !CASE_2

#if CASE_3
BOOST_AUTO_TEST_CASE(case3) {
  // arrange
  using namespace snake;
  snake::GridCell cell;

  // act
  cell.setPlayer(0, Direction::LEFT, Direction::LEFT);
  cell.removePlayer();

  // assert
  BOOST_CHECK(BOARD_CELL_TYPE::EMPTY == cell.type);
}
#endif  // !CASE_3

#if CASE_4
BOOST_AUTO_TEST_CASE(case4) {
  // arrange
  using namespace snake;
  snake::GridCell cell;

  // act
  cell.placeApple();

  // assert
  BOOST_CHECK(BOARD_CELL_TYPE::APPLE == cell.type);
}
#endif  // !CASE_4

#if CASE_5
BOOST_AUTO_TEST_CASE(case5) {
  // arrange
  using namespace snake;
  snake::GridCell cell;

  // act
  cell.placeApple();
  cell.pickupApple();

  // assert
  BOOST_CHECK(BOARD_CELL_TYPE::EMPTY == cell.type);
}
#endif  // !CASE_5