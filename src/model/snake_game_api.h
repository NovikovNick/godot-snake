#ifndef SNAKE_GAME_API_H_
#define SNAKE_GAME_API_H_
#include <iostream>

#include "direction.h"
#include "game_status.h"
#include "tile.h"

namespace snake {

class SnakeGameAPI {
 public:
  virtual ~SnakeGameAPI() = default;

  virtual void start() = 0;
  virtual void stop() = 0;
  virtual void move(const int player_id) = 0;
  virtual Tile getTile(const int row, const int col) const = 0;
  virtual GAME_STATUS getGameStatus() const = 0;
  virtual int getPlayerScore(const int player_id) const = 0;
  virtual void updateInput(const Direction fst_player_input,
                           const Direction snd_player_input,
                           int disconnect_flags) = 0;
};
}  // namespace snake

#endif  // SNAKE_GAME_API_H_
