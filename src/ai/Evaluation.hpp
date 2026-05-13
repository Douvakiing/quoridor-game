#ifndef EVALUATION_HPP
#define EVALUATION_HPP

#include "core/Board.hpp"
#include "core/GameState.hpp"
#include "core/Rules.hpp"
#include "core/Types.hpp"

namespace quoridor::Evaluation {

double evaluateState(
    const GameState& state,
    const Board& board,
    const Rules& rules,
    Player aiPlayer
);

double terminalScore(const GameState& state, Player aiPlayer);
Position getPositionForPlayer(const GameState& state, Player player);
int getWallsForPlayer(const GameState& state, Player player);

} // namespace quoridor::Evaluation

#endif
