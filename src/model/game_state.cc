#include "game_state.h"

#include <random>
#include <unordered_map>

#include "../util/log.h"
#include "ai_util.h"
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

snake::GameSettings getDefaultGameSetting() {
  using namespace snake;
  GameSettings setting;
  setting.width = 10;
  setting.height = 10;
  setting.max_score = 10;
  setting.fst_player = {{1, 4, Direction::BOTTOM, Direction::UP},
                        {1, 3, Direction::BOTTOM, Direction::UP},
                        {1, 2, Direction::BOTTOM, Direction::UP},
                        {1, 1, Direction::BOTTOM, Direction::NONE}};
  setting.snd_player = {{9, 4, Direction::BOTTOM, Direction::UP},
                        {9, 3, Direction::BOTTOM, Direction::UP},
                        {9, 2, Direction::BOTTOM, Direction::UP},
                        {9, 1, Direction::BOTTOM, Direction::NONE}};
  setting.apple = Coord{8, 8};
  return setting;
}

}  // namespace

namespace snake {

GameState::GameState()
    : framenumber(0),
      width(10),
      height(10),
      grid(std::vector<GridCell>(100)),
      max_score(10),
      status(GAME_STATUS::STOPED),
      apple(Coord{0, 0}) {}

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
  if (status != GAME_STATUS::PLAYING) return;

  auto& head_coord = players[player_id].head;
  auto& head_cell = getCell(head_coord);

  auto next_head_coord = move(head_coord, head_cell.next);
  auto& next_head_cell = getCell(next_head_coord);
  if (next_head_cell.isPlayer(0) || next_head_cell.isPlayer(1)) {
    status = player_id == 1 ? GAME_STATUS::SND_PLAYER_COLLIDED
                            : GAME_STATUS::FST_PLAYER_COLLIDED;
    return;
  }

  if (next_head_cell.isApple()) {
    next_head_cell.pickupApple();
    if (++players[player_id].score >= max_score) {
      status = player_id == 1 ? GAME_STATUS::SND_PLAYER_REACHED_SCORE
                              : GAME_STATUS::FST_PLAYER_REACHED_SCORE;
    }
    placeApple();
  } else {
    moveTail(player_id);
  }

  head_cell.tile =
      TileIndexUtil::getTurnTileIndex(head_cell.next, head_cell.prev);
  next_head_cell.setHead(player_id, head_cell.next, apposite(head_cell.next));

  head_coord = next_head_coord;
}

void GameState::placeApple() {
  // TODO: make apple generation deterministic

  std::random_device rd;
  std::mt19937 gen(rd());

  int row_gen = gen() % height;
  int col_gen = gen() % width;

  for (int row = row_gen; row < height; ++row) {
    for (int col = col_gen; col < width; ++col) {
      auto& cell = getCell({col, row});
      if (cell.canBeApple()) {
        cell.placeApple();
        apple = {col, row};
        return;
      }
    }
  }

  for (int row = 0; row < row_gen; ++row) {
    for (int col = 0; col < col_gen; ++col) {
      auto& cell = getCell({col, row});
      if (cell.canBeApple()) {
        cell.placeApple();
        apple = {col, row};
        return;
      }
    }
  }
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

void GameState::start() {
  GameSettings setting = getDefaultGameSetting();
  start(setting);
}

void GameState::start(const int width, const int height, const int max_score) {
  GameSettings setting = getDefaultGameSetting();
  setting.width = width;
  setting.height = height;
  setting.max_score = max_score;
  start(setting);
}

void GameState::start(const GameSettings& settings) {
  framenumber = 0;
  width = settings.width;
  height = settings.height;
  max_score = settings.max_score;
  grid = std::vector(settings.width * settings.height, GridCell{});

  initPlayer(0, settings.fst_player);
  initPlayer(1, settings.snd_player);

  apple = settings.apple;
  getCell(settings.apple).placeApple();

  status = GAME_STATUS::PLAYING;
}

bool GameState::isEmpty(const Coord coord) const {
  return grid[coord.row * width + coord.col].type == BOARD_CELL_TYPE::EMPTY;
}

void GameState::stop() { status = GAME_STATUS::STOPED; }

Tile GameState::getTile(const int col, const int row) const {
  auto cell = grid[row * GameState::width + col];
  if (cell.isApple()) return Tile::apple();
  if (cell.isPlayer(0)) return Tile::player(0, cell.tile);
  if (cell.isPlayer(1)) return Tile::player(1, cell.tile);
  return Tile::empty();
}

GAME_STATUS GameState::getGameStatus() const { return status; }

int GameState::getPlayerScore(const int player_id) const {
  return players[player_id].score;
}

void GameState::calculateInput(const int player_id) {
  updateInput(player_id, AIUtil::aStar(players[player_id].head, *this), 0);
}

void GameState::updateInput(const int player_id, const Direction input,
                            const int disconnect_flags) {
  if (input != Direction::NONE) getCell(players[player_id].head).next = input;
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