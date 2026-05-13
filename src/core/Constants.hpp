#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include "Types.hpp"

namespace quoridor::Constants {

constexpr int BOARD_SIZE = 9;
constexpr int WALLS_PER_PLAYER = 10;

const Position PLAYER_1_START{0, 4};
const Position PLAYER_2_START{8, 4};

constexpr int PLAYER_1_GOAL_ROW = 8;
constexpr int PLAYER_2_GOAL_ROW = 0;

} // namespace quoridor::Constants

#endif
