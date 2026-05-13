#include "ai/GreedyAI.hpp"
#include "ai/Evaluation.hpp"

#include <limits>

namespace quoridor {

GreedyAI::GreedyAI(Player player, const Board& boardRef, const Rules& rulesRef)
    : aiPlayer(player), board(boardRef), rules(rulesRef) {}

Move GreedyAI::chooseMove(const GameState& state) {
    auto moves = generateCandidateMoves(state);
    if (moves.empty()) {
        return Move::pawnMove(state.getPlayerPosition(aiPlayer));
    }

    Move bestMove = moves.front();
    double bestScore = -std::numeric_limits<double>::infinity();
    for (const auto& move : moves) {
        double score = scoreMove(state, move);
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }
    return bestMove;
}

std::vector<Move> GreedyAI::generateCandidateMoves(const GameState& state) const {
    std::vector<Move> moves;
    for (const auto& position : rules.getLegalPawnMoves(state, aiPlayer)) {
        moves.push_back(Move::pawnMove(position));
    }
    // Add wall candidates later: start with pawn moves for a reliable first milestone.
    return moves;
}

double GreedyAI::scoreMove(const GameState& state, const Move& move) const {
    return Evaluation::evaluateState(simulateMove(state, move), board, rules, aiPlayer);
}

GameState GreedyAI::simulateMove(const GameState& state, const Move& move) const {
    GameState next = state.clone();
    if (move.type == MoveType::PawnMove && move.destination.has_value()) {
        next.setPlayerPosition(aiPlayer, move.destination.value());
    } else if (move.type == MoveType::WallPlacement && move.wall.has_value()) {
        next.addWall(move.wall.value());
        next.decrementWalls(aiPlayer);
    }

    if (auto winner = rules.checkWinner(next); winner.has_value()) {
        next.setWinner(winner.value());
    }
    next.switchTurn();
    return next;
}

} // namespace quoridor
