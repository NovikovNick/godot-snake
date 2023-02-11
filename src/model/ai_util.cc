#include "ai_util.h"

#include "board_cell_type.h"
#include "queue"

namespace {

struct Path {
  snake::Coord curr;
  snake::Direction dir;
  float distance;
  int length;

  Path(snake::Direction dir, snake::Coord coord, float distance, int length)
      : curr(coord), dir(dir), distance(distance), length(length){};

  Path() : Path(snake::Direction::NONE, {}, INT_MAX, INT_MAX){};
};

struct PathGreater {
  bool operator()(const Path& lhs, const Path& rhs) const {
    if (lhs.distance > rhs.distance) return true;
    if (lhs.distance == rhs.distance) return lhs.length > rhs.length;
    return false;
  }
};

inline float distance(const snake::Coord& lhs, const snake::Coord& rhs) {
  return sqrt(pow(lhs.row - rhs.row, 2) + pow(lhs.col - rhs.col, 2) * 1.0);
}

std::vector<Path> dp(1000);
std::vector<std::pair<snake::Coord, snake::Direction>> dirs{
    {{1, 0}, snake::Direction::RIGHT},
    {{-1, 0}, snake::Direction::LEFT},
    {{0, 1}, snake::Direction::BOTTOM},
    {{0, -1}, snake::Direction::UP}};
PathGreater greater;

bool operator!=(const Path& lhs, const Path& rhs) {
  return lhs.distance != rhs.distance || lhs.length != rhs.length;
}

bool operator==(const Path& lhs, const Path& rhs) {
  return lhs.distance == rhs.distance && lhs.length == rhs.length;
}

}  // namespace

namespace snake {

Direction AIUtil::aStar(const Coord from, const GameState& gs) {
  int max_count = gs.height * gs.width;
  std::fill(dp.begin(), dp.begin() + max_count, Path{});

  std::priority_queue<Path, std::vector<Path>, PathGreater> min_heap(greater);

  for (const auto [vector, dir] : dirs) {
    auto coord = Coord::plus(from, vector);

    if (Coord::equal(coord, gs.apple)) return dir;
    if (coord.col < 0 || coord.row < 0) continue;
    if (coord.col >= gs.width || coord.row >= gs.height) continue;
    if (!gs.isEmpty(coord)) continue;

    Path path(dir, coord, distance(coord, gs.apple), 1);
    min_heap.push(path);
    dp[coord.row * gs.width + coord.col] = path;
  }

  int count = 0;
  while (!min_heap.empty()) {
    if (++count > max_count) return Direction::NONE;

    auto path = min_heap.top();
    min_heap.pop();

    for (const auto [vector, dir] : dirs) {
      auto coord = Coord::plus(path.curr, vector);

      if (Coord::equal(coord, gs.apple)) return path.dir;
      if (coord.col < 0 || coord.row < 0) continue;
      if (coord.col >= gs.width || coord.row >= gs.height) continue;
      if (!gs.isEmpty(coord)) continue;

      Path next_path(path.dir, coord, distance(coord, gs.apple), path.length + 1);
      auto& visited = dp[coord.row * gs.width + coord.col];
      if (greater(path, visited) || path == visited) continue;

      min_heap.push(next_path);
      visited = next_path;
    }
  }
  return Direction::NONE;
}

}  // namespace snake
