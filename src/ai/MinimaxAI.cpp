#include "ai/MinimaxAI.hpp"
#include "ai/Evaluation.hpp"
#include "ai/MoveOrdering.hpp"

#include <limits>

namespace quoridor {

MinimaxAI::MinimaxAI(Player player, const Board& boardRef, const Rules& rulesRef, int depth)
    : aiPlayer(player), board(boardRef), rules(rulesRef), maxDepth(depth) {}

Move MinimaxAI::chooseMove(const GameState& state) {
    auto moves = MoveOrdering::orderMoves(state, generateCandidateMoves(state), board, rules, aiPlayer);
    if (moves.empty()) {
        return Move::pawnMove(state.getPlayerPosition(aiPlayer));
    }

    Move bestMove = moves.front();
    double bestScore = -std::numeric_limits<double>::infinity();

    for (const auto& move : moves) {
        GameState child = simulateMove(state, move, aiPlayer);
        double score = minimax(child, maxDepth - 1,
            -std::numeric_limits<double>::infinity(),
            std::numeric_limits<double>::infinity(),
            false);
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }

    return bestMove;
}

double MinimaxAI::minimax(const GameState& state, int depth, double alpha, double beta, bool maximizing) {
    if (depth == 0 || state.isGameOver()) {
        return Evaluation::evaluateState(state, board, rules, aiPlayer);
    }

    auto moves = MoveOrdering::orderMoves(state, generateCandidateMoves(state), board, rules, aiPlayer);
    if (moves.empty()) {
        return Evaluation::evaluateState(state, board, rules, aiPlayer);
    }

    Player player = state.getCurrentPlayer();

    if (maximizing) {
        double value = -std::numeric_limits<double>::infinity();
        for (const auto& move : moves) {
            value = std::max(value, minimax(simulateMove(state, move, player), depth - 1, alpha, beta, false));
            alpha = std::max(alpha, value);
            if (beta <= alpha) {
                break;
            }
        }
        return value;
    }

    double value = std::numeric_limits<double>::infinity();
    for (const auto& move : moves) {
        value = std::min(value, minimax(simulateMove(state, move, player), depth - 1, alpha, beta, true));
        beta = std::min(beta, value);
        if (beta <= alpha) {
            break;
        }
    }
    return value;
}

std::vector<Move> MinimaxAI::generateCandidateMoves(const GameState& state) const {
    Player player = state.getCurrentPlayer();
    auto moves = generateCandidatePawnMoves(state, player);
    auto walls = generateCandidateWallMoves(state, player);
    moves.insert(moves.end(), walls.begin(), walls.end());
    return moves;
}

std::vector<Move> MinimaxAI::generateCandidatePawnMoves(const GameState& state, Player player) const {
    std::vector<Move> moves;
    for (const auto& position : rules.getLegalPawnMoves(state, player)) {
        moves.push_back(Move::pawnMove(position));
    }
    return moves;
}

std::vector<Move> MinimaxAI::generateCandidateWallMoves(const GameState& state, Player player) const {
    std::vector<Move> moves;
    if (state.getWallsRemaining(player) <= 0) {
        return moves;
    }

    // Simple candidate generation: try walls close to the opponent.
    Position opponent = state.getPlayerPosition(opponentOf(player));
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            int row = opponent.row + dr;
            int col = opponent.col + dc;
            for (auto orientation : {WallOrientation::Horizontal, WallOrientation::Vertical}) {
                Wall wall{row, col, orientation};
                GameState temp = state.clone();
                temp.setCurrentPlayer(player);
                if (rules.isLegalWallPlacement(temp, wall)) {
                    moves.push_back(Move::wallPlacement(wall));
                }
            }
        }
    }
    return moves;
}

GameState MinimaxAI::simulateMove(const GameState& state, const Move& move, Player player) const {
    GameState next = state.clone();
    next.setCurrentPlayer(player);

    if (move.type == MoveType::PawnMove && move.destination.has_value()) {
        next.setPlayerPosition(player, move.destination.value());
    } else if (move.type == MoveType::WallPlacement && move.wall.has_value()) {
        next.addWall(move.wall.value());
        next.decrementWalls(player);
    }

    if (auto winner = rules.checkWinner(next); winner.has_value()) {
        next.setWinner(winner.value());
    } else {
        next.switchTurn();
    }
    return next;
}

} // namespace quoridor
