#include "grid_cell.h"

#include <bitset>

namespace {

uint8_t dir_msk = 0b11000000;
uint8_t prev_mask = 0b00110000;
uint8_t player_id_mask = 0b00001000;
uint8_t apple_mask = 0b00000110;
uint8_t curr_apple = (3 << 1);
uint8_t prev_apple = (2 << 1);

int empty_b = 0b00000001;

}  // namespace

namespace snake {

GridCell::GridCell(const Direction next, const Direction prev,
                   const BOARD_CELL_TYPE type, const uint8_t player_id,
                   const bool can_be_apple)
    : next(next),
      prev(prev),
      type(type),
      player_id(player_id),
      can_be_apple(can_be_apple){};

GridCell::GridCell()
    : GridCell(Direction::NONE, Direction::NONE, BOARD_CELL_TYPE::EMPTY, -1,
               true){};

bool GridCell::isApple() const {
  return type == BOARD_CELL_TYPE::APPLE;
}

bool GridCell::isPlayer(const uint8_t id) const {
  return type == BOARD_CELL_TYPE::PLAYER && player_id == id;
}

bool GridCell::isTail() const {
  return type == BOARD_CELL_TYPE::PLAYER && prev == Direction::NONE;
}

void GridCell::setTail() {
  type = BOARD_CELL_TYPE::PLAYER;
  prev = Direction::NONE;
}

void GridCell::removePlayer() {
  next = Direction::NONE;
  prev = Direction::NONE;
  type = BOARD_CELL_TYPE::EMPTY;
  player_id = -1;
}

void GridCell::placeApple() {
  type = BOARD_CELL_TYPE::APPLE;
}

void GridCell::pickupApple() {
  type = BOARD_CELL_TYPE::EMPTY;
}

void GridCell::setPlayer(const uint8_t id, Direction dir, Direction prev_) {
  type = BOARD_CELL_TYPE::PLAYER;
  player_id = id;
  next = dir;
  prev = prev_;
};

}  // namespace snake