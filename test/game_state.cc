#define BOOST_TEST_MODULE SolutionTest
#define CASE_1 0
#define CASE_2 1
#define CASE_3 0
#define CASE_4 0
#define CASE_5 0
#define CASE_6 0
#define CASE_7 0
#define DEBUG 1

#include "../src/model/game_state.h"

#include <bitset>
#include <boost/test/included/unit_test.hpp>
#include <iostream>

#include "../src/model/snake_game_api.h"
#include "../src/util/log.h"

using namespace snake;

void print(const snake::GameState& gs) {
  util::debug("=================== \n");
  int width = gs.width;
  int height = gs.height;
  for (int i = 0; i < width * height; ++i) {
    auto row = i / width;
    auto col = i % width;

    auto tile = gs.getTile(col, row);

    std::string sign = "_";
    if (tile.type == snake::BOARD_CELL_TYPE::APPLE) sign = "A";
    if (tile.type == snake::BOARD_CELL_TYPE::PLAYER)
      sign = std::format("{}", static_cast<int>(tile.index));

    util::debug("{} ", sign);
    if (col == (width - 1)) util::debug("\n");
  }
};

void assertGrid(const GameState& gs,
                const std::vector<std::tuple<int, int, TILE_INDEX>>& p0,
                const std::vector<std::tuple<int, int, TILE_INDEX>>& p1,
                const std::pair<int, int> apple) {
  std::vector<TILE_INDEX> expected_grid(gs.width * gs.height,
                                        TILE_INDEX::EMPTY);
  for (const auto [x, y, index] : p0) expected_grid[gs.width * y + x] = index;
  for (const auto [x, y, index] : p1) expected_grid[gs.width * y + x] = index;
  expected_grid[gs.width * apple.second + apple.first] = TILE_INDEX::APPLE;

  for (int i = 0; i < gs.width * gs.height; ++i) {
    int row = i / gs.width;
    int col = i % gs.width;

    switch (expected_grid[i]) {
      case TILE_INDEX::APPLE:
        BOOST_TEST_INFO(std::format("expected an apple at[{}, {}]", col, row));
        BOOST_CHECK(gs.getTile(col, row).type == BOARD_CELL_TYPE::APPLE);
        break;
      case TILE_INDEX::EMPTY:
        BOOST_TEST_INFO(std::format("expected empty at[{}, {}]", col, row));
        BOOST_CHECK(gs.getTile(col, row).type == BOARD_CELL_TYPE::EMPTY);
        break;
      default:
        BOOST_TEST_INFO(std::format("expected player  at[{}, {}]", col, row));
        BOOST_CHECK(gs.getTile(col, row).type == BOARD_CELL_TYPE::PLAYER);
    }
  }
};

#if CASE_1
BOOST_AUTO_TEST_CASE(case1) {
  // arrange
  using namespace snake;
  GameState gs;
  GameSettings setting;
  setting.width = 10;
  setting.height = 10;
  setting.fst_player = {{1, 4, Direction::BOTTOM, Direction::UP},
                        {1, 3, Direction::BOTTOM, Direction::UP},
                        {1, 2, Direction::BOTTOM, Direction::UP},
                        {1, 1, Direction::BOTTOM, Direction::NONE}};
  setting.snd_player = {{9, 4, Direction::BOTTOM, Direction::UP},
                        {9, 3, Direction::BOTTOM, Direction::UP},
                        {9, 2, Direction::BOTTOM, Direction::UP},
                        {9, 1, Direction::BOTTOM, Direction::NONE}};
  setting.apple = Coord{8, 8};

  // act
  gs.start(setting);
  gs.updateInput(Direction::RIGHT, Direction::NONE, 0);
  for (int i = 0; i < 10; ++i) {
      // assert
    print(gs);
    // act
    gs.move(0);
  }

  assertGrid(gs,
             {{1, 1, TILE_INDEX::TAIL_TOP},
              {1, 2, TILE_INDEX::TAIL_TOP},
              {1, 3, TILE_INDEX::TAIL_TOP},
              {1, 4, TILE_INDEX::TAIL_TOP}},
             {{9, 1, TILE_INDEX::TAIL_TOP},
              {9, 2, TILE_INDEX::TAIL_TOP},
              {9, 3, TILE_INDEX::TAIL_TOP},
              {9, 4, TILE_INDEX::TAIL_TOP}},
             {8, 8});
}
#endif  // !CASE_1

#if CASE_2
BOOST_AUTO_TEST_CASE(case2) {
  // arrange
  using namespace snake;
  GameState gs;
  GameSettings setting;
  setting.max_score = 10;
  setting.width = 10;
  setting.height = 10;
  setting.fst_player = {{1, 4, Direction::BOTTOM, Direction::UP},
                        {1, 3, Direction::BOTTOM, Direction::UP},
                        {1, 2, Direction::BOTTOM, Direction::UP},
                        {1, 1, Direction::BOTTOM, Direction::NONE}};
  setting.snd_player = {{9, 4, Direction::BOTTOM, Direction::UP},
                        {9, 3, Direction::BOTTOM, Direction::UP},
                        {9, 2, Direction::BOTTOM, Direction::UP},
                        {9, 1, Direction::BOTTOM, Direction::NONE}};
  setting.apple = Coord{1, 8};

  // act
  gs.start(setting);
  for (int i = 0; i < 5; ++i) {
    // assert
    print(gs);
    // act
    gs.move(0);
  }
  util::debug("score is {}\n", gs.getPlayerScore(0));

  assertGrid(gs,
             {{1, 1, TILE_INDEX::TAIL_TOP},
              {1, 2, TILE_INDEX::TAIL_TOP},
              {1, 3, TILE_INDEX::TAIL_TOP},
              {1, 4, TILE_INDEX::TAIL_TOP}},
             {{9, 1, TILE_INDEX::TAIL_TOP},
              {9, 2, TILE_INDEX::TAIL_TOP},
              {9, 3, TILE_INDEX::TAIL_TOP},
              {9, 4, TILE_INDEX::TAIL_TOP}},
             {8, 8});
}
#endif  // !CASE_2

#if CASE_3
BOOST_AUTO_TEST_CASE(case3) {
  // arrange
  snake::GameState gs;
  gs.Init();
  // act
  gs.Update(new int[]{static_cast<int>(snake::Direction::UP), -1}, 0);
  gs.MoveShip(0);

  // assert
  print(gs);
  assertGrid(gs, {{2, 1}, {3, 1}, {4, 1}, {4, 0}},
             {{1, 9}, {2, 9}, {3, 9}, {4, 9}}, {8, 8});
}
#endif  // !CASE_3

#if CASE_4
BOOST_AUTO_TEST_CASE(case4) {
  // arrange
  snake::GameState gs;
  gs.Init();
  // act
  gs.Update(new int[]{static_cast<int>(snake::Direction::BOTTOM), -1}, 0);
  gs.MoveShip(0);
  gs.MoveShip(0);
  gs.MoveShip(0);
  gs.MoveShip(0);
  gs.Update(new int[]{static_cast<int>(snake::Direction::RIGHT), -1}, 0);
  gs.MoveShip(0);
  gs.MoveShip(0);
  gs.MoveShip(0);

  // assert
  print(gs);
  assertGrid(gs, {{4, 5}, {5, 5}, {6, 5}, {7, 5}},
             {{1, 9}, {2, 9}, {3, 9}, {4, 9}}, {8, 8});
}
#endif  // !CASE_4

#if CASE_5
BOOST_AUTO_TEST_CASE(case5) {
  // arrange
  snake::GameState gs;
  gs.Init();
  // act
  gs.Update(new int[]{static_cast<int>(snake::Direction::BOTTOM), -1}, 0);
  gs.MoveShip(0);
  gs.MoveShip(0);
  gs.MoveShip(0);
  gs.MoveShip(0);
  gs.Update(new int[]{static_cast<int>(snake::Direction::LEFT), -1}, 0);
  gs.MoveShip(0);
  gs.MoveShip(0);
  gs.MoveShip(0);

  // assert
  print(gs);
  assertGrid(gs, {{1, 5}, {2, 5}, {3, 5}, {4, 5}},
             {{1, 9}, {2, 9}, {3, 9}, {4, 9}}, {8, 8});
}
#endif  // !CASE_5

#if CASE_6
BOOST_AUTO_TEST_CASE(case6) {
  // arrange
  snake::GameState gs;
  gs.Init();

  // act
  gs.MoveShip(0);
  gs.MoveShip(0);
  gs.MoveShip(0);
  gs.MoveShip(0);
  gs.MoveShip(0);
  gs.MoveShip(0);
  gs.MoveShip(0);

  // assert
  print(gs);
  assertGrid(gs, {{0, 1}, {1, 1}, {8, 1}, {9, 1}},
             {{1, 9}, {2, 9}, {3, 9}, {4, 9}}, {8, 8});
}
#endif  // !CASE_6

#if CASE_7
BOOST_AUTO_TEST_CASE(case7) {
  // arrange
  snake::GameState gs;
  gs.Init();

  // act
  gs.MoveShip(0);
  gs.MoveShip(0);
  gs.Update(new int[]{static_cast<int>(snake::Direction::BOTTOM), -1}, 0);
  for (int i = 0; i < 10; ++i) gs.MoveShip(0);

  // assert
  print(gs);
  assertGrid(gs, {{6, 0}, {6, 1}, {6, 8}, {6, 9}},
             {{1, 9}, {2, 9}, {3, 9}, {4, 9}}, {8, 8});
}
#endif  // !CASE_7