#include "game_state.h"

#include "../util/log.h"
#include "grid_cell.h"

namespace {

snake::Direction apposite(snake::Direction dir) {
  switch (dir) {
    case snake::Direction::UP:
      return snake::Direction::BOTTOM;
    case snake::Direction::BOTTOM:
      return snake::Direction::UP;
    case snake::Direction::LEFT:
      return snake::Direction::RIGHT;
    case snake::Direction::RIGHT:
      return snake::Direction::LEFT;
    default:
      throw std::invalid_argument("no such direction");
  }
}

}  // namespace

namespace snake {

inline GridCell& GameState::getCell(const Coord coord) {
  return grid[coord.row * GameState::width + coord.col];
}

void GameState::initPlayers() {
  for (int id = 0; id < GameState::player_count; ++id) {
    auto& head = players[id].head;
    auto& tail = players[id].tail;

    auto [col_begin, col_end] = std::minmax(head.col, tail.col);
    for (int col = col_begin; col < col_end; ++col) {
      getCell({col, head.row}).setPlayer(id, Direction::RIGHT, Direction::LEFT);
    }

    auto [row_begin, row_end] = std::minmax(head.row, tail.row);
    for (int row = row_begin; row < row_end; ++row) {
      getCell({tail.col, row}).setPlayer(id, Direction::RIGHT, Direction::LEFT);
    }
  }
}

void GameState::move(const int player_id) {
  _framenumber++;
  auto head = players[player_id].head;

  auto next_head = move(head, getCell(head).getDir());
  getCell(next_head).setPlayer(player_id, getCell(head).getDir(),
                               apposite(getCell(head).getDir()));

  if (getCell(next_head).isApple()) {
    getCell(next_head).setPrevApple();
  } else {
    getCell(players[player_id].tail).setEmpty(true);
    // players[player_id].tail = next_head;
  }

  players[player_id].head = next_head;
}

void GameState::init(const GameSettings& settings) {
  _framenumber = 0;
  memset(grid, GridCell{}.data, sizeof(grid));
  players[0] = Player(settings.fst_player_head, settings.fst_player_tail);
  players[1] = Player(settings.snd_player_head, settings.snd_player_tail);
  initPlayers();
  getCell(settings.apple).setCurrApple();
  status = 0;
}

void GameState::init() {
  GameSettings setting;
  setting.fst_player_head = Coord{4, 1};
  setting.fst_player_tail = Coord{1, 1};
  setting.snd_player_head = Coord{4, 9};
  setting.snd_player_tail = Coord{1, 9};
  setting.apple = Coord{8, 8};
  init(setting);
}

TILE_INDEX GameState::getCellTailIndex(const int row, const int col) const {
  auto cell = grid[row * GameState::width + col];
  if (cell.isApple()) return TILE_INDEX::APPLE;
  if (cell.isPlayer(0)) return TILE_INDEX::BODY_HOR_P1;
  if (cell.isPlayer(1)) return TILE_INDEX::BODY_HOR_P2;
  return TILE_INDEX::EMPTY;
}

void GameState::getGameState() const {}

void GameState::update(const int fst_player_input, const int snd_player_input,
                       int disconnect_flags) {
  /*if (fst_player_input != -1) {
    auto& head = getGridCell(grid, players[0].x, players[0].y);
    auto dir = static_cast<Direction>(fst_player_input);
    head.setPlayer(0, dir, head.getPrev());
  }

  if (snd_player_input != -1) {
    auto& head = getGridCell(grid, players[1].x, players[1].y);
    auto dir = static_cast<Direction>(snd_player_input);
    head.setPlayer(1, dir, head.getPrev());
  }*/
}

Coord GameState::move(Coord pos, snake::Direction dir) {
  switch (dir) {
    case snake::Direction::UP:
      return (pos.row == 0) ? Coord{pos.col, GameState::height - 1}
                            : Coord{pos.col, pos.row - 1};
    case snake::Direction::BOTTOM:
      return (pos.row == GameState::height - 1) ? Coord{pos.col, 0}
                                                : Coord{pos.col, pos.row + 1};
    case snake::Direction::LEFT:
      return (pos.col == 0) ? Coord{GameState::width - 1, pos.row}
                            : Coord{pos.col - 1, pos.row};
    case snake::Direction::RIGHT:
      return (pos.col == GameState::width - 1) ? Coord{0, pos.col}
                                               : Coord{pos.col + 1, pos.row};
    default:
      throw std::invalid_argument("no such direction");
  }
}

}  // namespace snake