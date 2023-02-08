#include "tile_index_util.h"

#include <unordered_map>

bool operator==(const KEY& lhs, const KEY& rhs) {
  return lhs.first == rhs.first && lhs.second == rhs.second;
};

namespace std {
template <>
struct hash<KEY> {
  size_t operator()(const KEY& val) const {
    auto h1 = hash<int>{}(static_cast<int>(val.first));
    auto h2 = hash<int>{}(static_cast<int>(val.second));
    return h1 == h2 ? h1 : h1 ^ h2;
  }
};
}  // namespace std

namespace snake {

TILE_INDEX TileIndexUtil::getTurnTileIndex(const Direction prev,
                                                  const Direction next) {
  return tile_to_dir[{prev, next}];
}

TILE_INDEX TileIndexUtil::getHeadTileIndex(const Direction next) {
  switch (next) {
    case Direction::UP:
      return TILE_INDEX::HEAD_TOP;
    case Direction::BOTTOM:
      return TILE_INDEX::HEAD_BTM;
    case Direction::LEFT:
      return TILE_INDEX::HEAD_LFT;
    case Direction::RIGHT:
      return TILE_INDEX::HEAD_RHT;
  }
}

TILE_INDEX TileIndexUtil::getTailTileIndex(const Direction next) {
  switch (next) {
    case Direction::UP:
      return TILE_INDEX::TAIL_BTM;
    case Direction::BOTTOM:
      return TILE_INDEX::TAIL_TOP;
    case Direction::LEFT:
      return TILE_INDEX::TAIL_RHT;
    case Direction::RIGHT:
      return TILE_INDEX::TAIL_LFT;
  }
}

std::unordered_map<KEY, TILE_INDEX> TileIndexUtil::tile_to_dir = {
    {{Direction::UP, Direction::BOTTOM}, TILE_INDEX::BODY_VER},
    {{Direction::BOTTOM, Direction::UP}, TILE_INDEX::BODY_VER},

    {{Direction::LEFT, Direction::RIGHT}, TILE_INDEX::BODY_HOR},
    {{Direction::RIGHT, Direction::LEFT}, TILE_INDEX::BODY_HOR},

    {{Direction::BOTTOM, Direction::LEFT}, TILE_INDEX::TURN_BL},
    {{Direction::LEFT, Direction::BOTTOM}, TILE_INDEX::TURN_BL},

    {{Direction::BOTTOM, Direction::RIGHT}, TILE_INDEX::TURN_BR},
    {{Direction::RIGHT, Direction::BOTTOM}, TILE_INDEX::TURN_BR},

    {{Direction::UP, Direction::LEFT}, TILE_INDEX::TURN_TL},
    {{Direction::LEFT, Direction::UP}, TILE_INDEX::TURN_TL},

    {{Direction::UP, Direction::RIGHT}, TILE_INDEX::TURN_TR},
    {{Direction::RIGHT, Direction::UP}, TILE_INDEX::TURN_TR}};

}  // namespace snake

