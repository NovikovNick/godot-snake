#include "snake_board.h"

#include "model/direction.h"
#include "model/tile.h"

using namespace godot;

void Board::_register_methods() {
  godot::register_method("get_cell", &godot::Board::getCell);
  godot::register_method("start", &godot::Board::start);
  godot::register_method("start_with_settings", &godot::Board::startWithSettings);
  godot::register_method("stop", &godot::Board::stop);
  godot::register_method("move", &godot::Board::move);
  godot::register_method("update_input", &godot::Board::updateInput);
  godot::register_method("calculate_input", &godot::Board::calculateInput);
  godot::register_method("get_status", &godot::Board::getStatus);
  godot::register_method("get_player_score", &godot::Board::getPlayerScore);
}

void Board::_init() { api = std::make_unique<snake::GameState>(); }

int Board::getCell(const int x, const int y) {
  return static_cast<int>(api->getTile(x, y).index);
}

void Board::start() { api->start(); }

void Board::startWithSettings(const int width, const int height,
                              const int max_score) {
  api->start(width, height, max_score);
}

void Board::stop() { api->stop(); }

int Board::getStatus() { return static_cast<int>(api->getGameStatus()); }

int Board::getPlayerScore(const int player_id) {
  return api->getPlayerScore(player_id);
}

void Board::move(const int player_id) { api->move(player_id); }

void Board::updateInput(const int player_id, const int dir) {
  api->updateInput(player_id, static_cast<snake::Direction>(dir), 0);
}

void Board::calculateInput(const int player_id) {
  api->calculateInput(player_id);
}
