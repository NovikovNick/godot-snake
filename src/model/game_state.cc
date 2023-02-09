#include "game_state.h"

#include <unordered_map>

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

snake::Direction dir(const snake::Coord from, const snake::Coord to) {}

}  // namespace

namespace snake {

inline GridCell& GameState::getCell(const Coord coord) {
  return grid[coord.row * GameState::width + coord.col];
}

void GameState::initPlayer(
    const int id,
    const std::vector<std::tuple<int, int, Direction, Direction>>& segments) {
  int n = segments.size();
  for (int i = 0; i < n; ++i) {
    auto [col, row, next, prev] = segments[i];
    auto& cell = getCell({col, row});
    if (i == 0) {
      players[id] = Player({col, row});
      cell.setHead(id, next, prev);
    } else if (i == n - 1) {
      cell.setPlayer(id, next, prev);
      cell.setTail();
    } else {
      cell.setPlayer(id, next, prev);
      cell.tile = TileIndexUtil::getTurnTileIndex(next, prev);
    }
  }
}

void GameState::move(const int player_id) {
  framenumber++;
  auto& head_coord = players[player_id].head;
  auto& head_cell = getCell(head_coord);

  auto next_head_coord = move(head_coord, head_cell.next);
  auto& next_head_cell = getCell(next_head_coord);

  head_cell.tile =
      TileIndexUtil::getTurnTileIndex(head_cell.next, head_cell.prev);
  next_head_cell.setHead(player_id, head_cell.next, apposite(head_cell.next));

  if (next_head_cell.isApple()) {
    next_head_cell.pickupApple();
  } else {
    moveTail(player_id);
  }

  head_coord = next_head_coord;
}

void GameState::moveTail(const int player_id) {
  Coord tail_coord = players[player_id].head;
  Coord prev_coord = tail_coord;
  while (!getCell(tail_coord).isTail()) {
    prev_coord = tail_coord;
    tail_coord = move(tail_coord, getCell(tail_coord).prev);
  };
  getCell(prev_coord).setTail();
  getCell(tail_coord).removePlayer();
}

GameState::GameState()
    : framenumber(0),
      width(10),
      height(10),
      grid(std::vector<GridCell>(100)),
      status(GAME_STATUS::STOPED) {}

void GameState::init(const GameSettings& settings) {
  framenumber = 0;
  width = settings.width;
  height = settings.height;
  grid = std::vector(settings.width * settings.height, GridCell{});

  initPlayer(0, settings.fst_player);
  initPlayer(1, settings.snd_player);
  getCell(settings.apple).placeApple();

  status = GAME_STATUS::PLAYING;
}

void GameState::init() {
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
  init(setting);
}

Tile GameState::getTile(const int col, const int row) const {
  auto cell = grid[row * GameState::width + col];
  if (cell.isApple()) return Tile::apple();
  if (cell.isPlayer(0)) return Tile::player(0, cell.tile);
  if (cell.isPlayer(1)) return Tile::player(1, cell.tile);
  return Tile::empty();
}

GAME_STATUS GameState::getGameState() const { return GAME_STATUS::PLAYING; }

void GameState::updateInput(const Direction fst_player_input,
                            const Direction snd_player_input,
                            int disconnect_flags) {
  if (fst_player_input != Direction::NONE)
    getCell(players[0].head).next = fst_player_input;

  if (snd_player_input != Direction::NONE)
    getCell(players[1].head).next = snd_player_input;
}

Coord GameState::move(const Coord pos, const Direction dir) {
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
      return (pos.col == GameState::width - 1) ? Coord{0, pos.row}
                                               : Coord{pos.col + 1, pos.row};
    default:
      throw std::invalid_argument("no such direction");
  }
}

}  // namespace snake