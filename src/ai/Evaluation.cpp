#include "ai/Evaluation.hpp"
#include "core/Search.hpp"

namespace quoridor::Evaluation {

double terminalScore(const GameState& state, Player aiPlayer) {
    if (!state.getWinner().has_value()) {
        return 0.0;
    }
    return state.getWinner().value() == aiPlayer ? 10000.0 : -10000.0;
}

Position getPositionForPlayer(const GameState& state, Player player) {
    return state.getPlayerPosition(player);
}

int getWallsForPlayer(const GameState& state, Player player) {
    return state.getWallsRemaining(player);
}

double evaluateState(
    const GameState& state,
    const Board& board,
    const Rules& rules,
    Player aiPlayer
) {
    if (state.isGameOver()) {
        return terminalScore(state, aiPlayer);
    }

    Player opponent = opponentOf(aiPlayer);
    int aiPath = Search::bfsShortestPathLength(
        board,
        state.getPlayerPosition(aiPlayer),
        rules.getGoalRow(aiPlayer),
        state.getPlacedWalls()
    );
    int opponentPath = Search::bfsShortestPathLength(
        board,
        state.getPlayerPosition(opponent),
        rules.getGoalRow(opponent),
        state.getPlacedWalls()
    );

    return 3.0 * (opponentPath - aiPath)
        + 0.5 * (state.getWallsRemaining(aiPlayer) - state.getWallsRemaining(opponent));
}

} // namespace quoridor::Evaluation
