#ifndef MOVE_ORDERING_HPP
#define MOVE_ORDERING_HPP

#include "core/Board.hpp"
#include "core/GameState.hpp"
#include "core/Rules.hpp"
#include "core/Types.hpp"

#include <vector>

namespace quoridor::MoveOrdering {

std::vector<Move> orderMoves(
    const GameState& state,
    const std::vector<Move>& moves,
    const Board& board,
    const Rules& rules,
    Player aiPlayer
);

bool isPawnMove(const Move& move);
bool isWallMove(const Move& move);

double quickMoveScore(
    const GameState& state,
    const Move& move,
    const Board& board,
    const Rules& rules,
    Player aiPlayer
);

} // namespace quoridor::MoveOrdering

#endif
