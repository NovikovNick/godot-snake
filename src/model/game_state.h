#ifndef SNAKE_GAME_STATE_H_
#define SNAKE_GAME_STATE_H_
#include <iostream>

#include "grid_cell.h"
#include "snake_game_api.h"

namespace snake {

struct Coord {
  int row, col;
};

struct GameSettings {
  Coord fst_player_head, fst_player_tail;
  Coord snd_player_head, snd_player_tail;
  Coord apple;
};

struct Player final {
  Coord head, tail;
  uint8_t score;
  Player(Coord head, Coord tail) : head(head), tail(tail), score(0){};
  Player() : Player({0, 0}, {0, 0}){};
};

class GameState : public SnakeGameAPI {
 public:
  const static int width = 10;
  const static int height = 10;
  const static int player_count = 2;

  void init(const GameSettings& settings);
  void init() override;
  void move(const int player_id) override;
  TILE_INDEX getCellTailIndex(const int row, const int col) const override;
  void getGameState() const override;
  void update(const int fst_player_input, const int snd_player_input,
              int disconnect_flags) override;

 private:
  GridCell grid[width * height];
  Player players[player_count];
  uint8_t status;
  int _framenumber;

  Coord move(const Coord pos, const snake::Direction dir);
  GridCell& getCell(const Coord coord);
  void initPlayers();
};
}  // namespace snake

#endif  // SNAKE_GAME_STATE_H_
