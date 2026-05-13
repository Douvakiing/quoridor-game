#ifndef MINIMAX_AI_HPP
#define MINIMAX_AI_HPP

#include "core/Board.hpp"
#include "core/GameState.hpp"
#include "core/Rules.hpp"
#include "core/Types.hpp"

#include <vector>

namespace quoridor {

class MinimaxAI {
private:
    Player aiPlayer;
    const Board& board;
    const Rules& rules;
    int maxDepth;

public:
    MinimaxAI(Player player, const Board& boardRef, const Rules& rulesRef, int depth = 2);
    Move chooseMove(const GameState& state);

private:
    double minimax(const GameState& state, int depth, double alpha, double beta, bool maximizing);
    std::vector<Move> generateCandidateMoves(const GameState& state) const;
    std::vector<Move> generateCandidatePawnMoves(const GameState& state, Player player) const;
    std::vector<Move> generateCandidateWallMoves(const GameState& state, Player player) const;
    GameState simulateMove(const GameState& state, const Move& move, Player player) const;
};

} // namespace quoridor

#endif
