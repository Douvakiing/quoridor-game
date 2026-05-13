#include "ai/MoveOrdering.hpp"
#include "ai/Evaluation.hpp"

#include <algorithm>

namespace quoridor::MoveOrdering {

std::vector<Move> orderMoves(
    const GameState& state,
    const std::vector<Move>& moves,
    const Board& board,
    const Rules& rules,
    Player aiPlayer
) {
    std::vector<Move> ordered = moves;
    std::sort(ordered.begin(), ordered.end(), [&](const Move& a, const Move& b) {
        return quickMoveScore(state, a, board, rules, aiPlayer)
            > quickMoveScore(state, b, board, rules, aiPlayer);
    });
    return ordered;
}

bool isPawnMove(const Move& move) {
    return move.type == MoveType::PawnMove;
}

bool isWallMove(const Move& move) {
    return move.type == MoveType::WallPlacement;
}

double quickMoveScore(
    const GameState& state,
    const Move& move,
    const Board& board,
    const Rules& rules,
    Player aiPlayer
) {
    GameState next = state.clone();
    Player player = next.getCurrentPlayer();

    if (move.type == MoveType::PawnMove && move.destination.has_value()) {
        next.setPlayerPosition(player, move.destination.value());
    } else if (move.type == MoveType::WallPlacement && move.wall.has_value()) {
        next.addWall(move.wall.value());
        next.decrementWalls(player);
    }

    return Evaluation::evaluateState(next, board, rules, aiPlayer);
}

} // namespace quoridor::MoveOrdering
