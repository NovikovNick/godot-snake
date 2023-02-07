#ifndef SNAKE_GAME_STATUS_H_
#define SNAKE_GAME_STATUS_H_

namespace snake {

enum class GAME_STATUS {
  PLAYING = 0,
  FST_PLAYER_REACHED_SCORE = 1,
  SND_PLAYER_REACHED_SCORE = 2,
  FST_PLAYER_COLLIDED = 3,
  SND_PLAYER_COLLIDED = 4
};

}  // namespace snake
#endif  // SNAKE_GAME_STATUS_H_
