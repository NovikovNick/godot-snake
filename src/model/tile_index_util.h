#ifndef SNAKE_TILE_INDEX_UTIL_H_
#define SNAKE_TILE_INDEX_UTIL_H_
#include <unordered_map>

#include "direction.h"
#include "tile_index.h"

using KEY = std::pair<snake::Direction, snake::Direction>;

namespace snake {

class TileIndexUtil {
 public:
  static std::unordered_map<KEY, TILE_INDEX> tile_to_dir;

  static TILE_INDEX getTurnTileIndex(const Direction prev,
                                     const Direction next);

  static TILE_INDEX getHeadTileIndex(const Direction next);

  static TILE_INDEX getTailTileIndex(const Direction next);
};
}  // namespace snake
#endif  // SNAKE_TILE_INDEX_UTIL_H_
