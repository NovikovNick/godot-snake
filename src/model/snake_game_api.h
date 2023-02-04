#ifndef SNAKE_GAME_API_H_
#define SNAKE_GAME_API_H_
#include <iostream>

#include "tile_index.h"

namespace snake {

class SnakeGameAPI {
 public:
  virtual ~SnakeGameAPI() = default;

  virtual void init() = 0;
  virtual void move(const int player_id) = 0;
  virtual TILE_INDEX getCellTailIndex(const int row, const int col) const = 0;
  virtual void getGameState() const = 0;
  virtual void update(const int fst_player_input, 
                      const int snd_player_input,
                      int disconnect_flags) = 0;
};
}  // namespace snake

#endif  // SNAKE_GAME_API_H_
