#ifndef GREEDY_AI_HPP
#define GREEDY_AI_HPP

#include "core/Board.hpp"
#include "core/GameState.hpp"
#include "core/Rules.hpp"
#include "core/Types.hpp"

#include <vector>

namespace quoridor {

class GreedyAI {
private:
    Player aiPlayer;
    const Board& board;
    const Rules& rules;

public:
    GreedyAI(Player player, const Board& boardRef, const Rules& rulesRef);

    Move chooseMove(const GameState& state);
    std::vector<Move> generateCandidateMoves(const GameState& state) const;
    double scoreMove(const GameState& state, const Move& move) const;
    GameState simulateMove(const GameState& state, const Move& move) const;
};

} // namespace quoridor

#endif
