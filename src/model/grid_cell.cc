#include "grid_cell.h"

namespace snake {

GridCell::GridCell(const Direction next, const Direction prev,
                   const BOARD_CELL_TYPE type, const TILE_INDEX tile,
                   const uint8_t player_id, const bool can_be_apple)
    : next(next),
      prev(prev),
      type(type),
      tile(tile),
      player_id(player_id),
      can_be_apple(can_be_apple){};

GridCell::GridCell()
    : GridCell(Direction::NONE, Direction::NONE, BOARD_CELL_TYPE::EMPTY,
               TILE_INDEX ::EMPTY, -1, true){};

bool GridCell::isApple() const { return type == BOARD_CELL_TYPE::APPLE; }

bool GridCell::isPlayer(const uint8_t id) const {
  return type == BOARD_CELL_TYPE::PLAYER && player_id == id;
}

bool GridCell::isTail() const {
  return type == BOARD_CELL_TYPE::PLAYER && prev == Direction::NONE;
}

void GridCell::setTail() {
  type = BOARD_CELL_TYPE::PLAYER;
  prev = Direction::NONE;
  tile = TileIndexUtil::getTailTileIndex(next);
}

void GridCell::removePlayer() {
  next = Direction::NONE;
  prev = Direction::NONE;
  type = BOARD_CELL_TYPE::EMPTY;
  tile = TILE_INDEX::EMPTY;
  player_id = -1;
}

void GridCell::placeApple() {
  type = BOARD_CELL_TYPE::APPLE;
  tile = TILE_INDEX::APPLE;
  can_be_apple = false;
}

bool GridCell::canBeApple() {
  return type == BOARD_CELL_TYPE::EMPTY && can_be_apple;
}

void GridCell::pickupApple() {
  type = BOARD_CELL_TYPE::EMPTY;
  tile = TILE_INDEX::EMPTY;
}

void GridCell::setPlayer(const uint8_t id, Direction dir, Direction prev_) {
  type = BOARD_CELL_TYPE::PLAYER;
  player_id = id;
  next = dir;
  prev = prev_;
}

void GridCell::setHead(const uint8_t id, Direction dir, Direction prev) {
  setPlayer(id, dir, prev);
  tile = TileIndexUtil::getHeadTileIndex(dir);
}

}  // namespace snake