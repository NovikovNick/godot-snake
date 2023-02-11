#ifndef SNAKE_GAME_STATE_H_
#define SNAKE_GAME_STATE_H_
#include <iostream>
#include <vector>

#include "coord.h"
#include "direction.h"
#include "grid_cell.h"
#include "snake_game_api.h"

namespace snake {

struct GameSettings {
  uint8_t width, height, max_score;
  std::vector<std::tuple<int, int, Direction, Direction>> fst_player;
  std::vector<std::tuple<int, int, Direction, Direction>> snd_player;
  Coord apple;
};

struct Player final {
  Coord head;
  uint8_t score;
  Player(Coord head) : head(head), score(0){};
  Player() : Player({0, 0}){};
};

class GameState : public SnakeGameAPI {
 public:
  const static int player_count = 2;
  int framenumber, width, height, max_score;
  Coord apple;
  GameState();
  void start() override;
  void start(const int width, const int height, const int max_score) override;
  void stop() override;
  void move(const int player_id) override;
  Tile getTile(const int col, const int row) const override;
  GAME_STATUS getGameStatus() const override;
  int getPlayerScore(const int player_id) const override;
  void calculateInput(const int player_id) override;
  void updateInput(const int player_id, const Direction input,
                   const int disconnect_flags) override;

  void start(const GameSettings& settings);
  bool isEmpty(const Coord coord) const;

 private:
  std::vector<GridCell> grid;
  Player players[player_count];
  GAME_STATUS status;

  Coord move(const Coord pos, const Direction dir);
  GridCell& getCell(const Coord coord);
  void moveTail(const int player_id);
  void placeApple();
  void initPlayer(
      const int player_id,
      const std::vector<std::tuple<int, int, Direction, Direction>>& segments);
};
}  // namespace snake

#endif  // SNAKE_GAME_STATE_H_
