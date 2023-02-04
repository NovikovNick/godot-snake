#define BOOST_TEST_MODULE SolutionTest
#define CASE_1 1
#define CASE_2 0
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

void print(const snake::GameState& gs) {
  util::debug("-------------------\n");
  int width = snake::GameState::width;
  int height = snake::GameState::height;
  for (int i = 0; i < width * height; ++i) {
    auto row = i / width;
    auto col = i % width;

    auto sign = "";
    switch (gs.getCellTailIndex(col, row)) {
      case snake::TILE_INDEX::EMPTY:
        sign = " ";
        break;
      case snake::TILE_INDEX::APPLE:
        sign = "A";
        break;
      case snake::TILE_INDEX::BODY_HOR_P1:
        sign = "1";
        break;
      case snake::TILE_INDEX::BODY_VER_P1:
        sign = "1";
        break;
      case snake::TILE_INDEX::HEAD_TOP_P1:
        sign = "1";
        break;
      case snake::TILE_INDEX::HEAD_BTM_P1:
        sign = "1";
        break;
      case snake::TILE_INDEX::HEAD_LFT_P1:
        sign = "1";
        break;
      case snake::TILE_INDEX::HEAD_RHT_P1:
        sign = "1";
        break;
      case snake::TILE_INDEX::TAIL_TOP_P1:
        sign = "1";
        break;
      case snake::TILE_INDEX::TAIL_BTM_P1:
        sign = "1";
        break;
      case snake::TILE_INDEX::TAIL_LFT_P1:
        sign = "1";
        break;
      case snake::TILE_INDEX::TAIL_RHT_P1:
        sign = "1";
        break;
      case snake::TILE_INDEX::TURN_TL_P1:
        sign = "1";
        break;
      case snake::TILE_INDEX::TURN_TR_P1:
        sign = "1";
        break;
      case snake::TILE_INDEX::TURN_BL_P1:
        sign = "1";
        break;
      case snake::TILE_INDEX::TURN_BR_P1:
        sign = "1";
        break;
      case snake::TILE_INDEX::BODY_HOR_P2:
        sign = "2";
        break;
      case snake::TILE_INDEX::BODY_VER_P2:
        sign = "2";
        break;
      case snake::TILE_INDEX::HEAD_BTM_P2:
        sign = "2";
        break;
      case snake::TILE_INDEX::HEAD_LFT_P2:
        sign = "2";
        break;
      case snake::TILE_INDEX::TAIL_TOP_P2:
        sign = "2";
        break;
      case snake::TILE_INDEX::TAIL_BTM_P2:
        sign = "2";
        break;
      case snake::TILE_INDEX::TAIL_LFT_P2:
        sign = "2";
        break;
      case snake::TILE_INDEX::TAIL_RHT_P2:
        sign = "2";
        break;
      case snake::TILE_INDEX::TURN_TR_P2:
        sign = "2";
        break;
      case snake::TILE_INDEX::TURN_BL_P2:
        sign = "2";
        break;
      case snake::TILE_INDEX::TURN_BR_P2:
        sign = "2";
        break;
    }
    util::debug("{} ", sign);
    if ((col) == (width - 1)) util::debug("\n");
  }
};

void assertGrid(const snake::GameState& gs,
                const std::vector<std::pair<int, int>>& p0,
                const std::vector<std::pair<int, int>>& p1,
                const std::pair<int, int> apple){
    /*std::vector<char> expected_grid(gs.width * gs.height, ' ');
    for (const auto [x, y] : p0) expected_grid[gs.width * y + x] = '0';
    for (const auto [x, y] : p1) expected_grid[gs.width * y + x] = '1';
    expected_grid[gs.width * apple.second + apple.first] = 'a';

    for (int i = 0; i < gs.n * gs.n; ++i) {
      int row = i / gs.n;
      int col = i % gs.n;
      switch (expected_grid[i]) {
        case '0':
          BOOST_TEST_INFO(std::format("expected player 0 at[{}, {}]", col,
    row)); BOOST_CHECK(gs.grid[i].isPlayer() && gs.grid[i].isPlayer(0)); break;
        case '1':
          BOOST_TEST_INFO(std::format("expected player 1 at[{}, {}]", col,
    row)); BOOST_CHECK(gs.grid[i].isPlayer() && gs.grid[i].isPlayer(1)); break;
        case 'a':
          BOOST_TEST_INFO(std::format("expected an apple at[{}, {}]", col,
    row)); BOOST_CHECK(gs.grid[i].isApple()); break; default:
          BOOST_TEST_INFO(std::format("expected empty at[{}, {}]", col, row));
          BOOST_CHECK(gs.grid[i].isEmpty());
          break;
      }
    }*/
};

#if CASE_1
BOOST_AUTO_TEST_CASE(case1) {
  // arrange
  using namespace snake;
  GameState gs;
  GameSettings setting;
  setting.fst_player_head = Coord{4, 1};
  setting.fst_player_tail = Coord{1, 1};
  setting.snd_player_head = Coord{4, 9};
  setting.snd_player_tail = Coord{1, 9};
  setting.apple = Coord{8, 8};

  // act
  gs.init(setting);

  // assert
  print(gs);

  /*print(dynamic_cast<snake::GameState&>(api));
  assertGrid(dynamic_cast<snake::GameState&>(api),
             {{1, 1}, {2, 1}, {3, 1}, {4, 1}}, {{1, 9}, {2, 9}, {3, 9}, {4, 9}},
             {8, 8});*/
}
#endif  // !CASE_1

#if CASE_2
BOOST_AUTO_TEST_CASE(case2) {
  // arrange
  snake::GameState gs;
  gs.Init();

  // act
  gs.Update(new int[]{static_cast<int>(snake::Direction::BOTTOM), -1}, 0);
  gs.Move(0);

  // assert
  print(gs);
  assertGrid(gs, {{2, 1}, {3, 1}, {4, 1}, {4, 2}},
             {{1, 9}, {2, 9}, {3, 9}, {4, 9}}, {8, 8});
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