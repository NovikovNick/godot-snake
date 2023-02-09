#include "snake_board.h"

#include "model/direction.h"
#include "model/tile.h"

using namespace godot;

void Board::_register_methods() {
  godot::register_method("get_cell", &godot::Board::getCell);
  godot::register_method("start", &godot::Board::start);
  godot::register_method("move", &godot::Board::move);
  godot::register_method("update_input", &godot::Board::updateInput);
}

void Board::_init() { api = std::make_unique<snake::GameState>(); }

int Board::getCell(const int x, const int y) {
  return static_cast<int>(api->getTile(x, y).index);
}

void Board::start() { api->init(); }

void Board::move(const int player_id) { api->move(player_id); }

void Board::updateInput(const int dir) {
  using namespace snake;
  api->updateInput(static_cast<Direction>(dir), Direction::NONE, 0);
}
