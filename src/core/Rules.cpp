#include "Rules.hpp"
#include "Search.hpp"

#include <algorithm>

namespace quoridor {

Rules::Rules(const Board& boardRef) : board(boardRef) {}

std::vector<Position> Rules::getLegalPawnMoves(const GameState& state, Player player) const {
    std::vector<Position> moves = getNormalMoves(state, player);
    auto jumps = getJumpMoves(state, player);
    auto diagonals = getDiagonalMovesAroundOpponent(state, player);

    moves.insert(moves.end(), jumps.begin(), jumps.end());
    moves.insert(moves.end(), diagonals.begin(), diagonals.end());

    std::sort(moves.begin(), moves.end());
    moves.erase(std::unique(moves.begin(), moves.end()), moves.end());
    return moves;
}

bool Rules::isLegalPawnMove(const GameState& state, Player player, Position destination) const {
    auto moves = getLegalPawnMoves(state, player);
    return std::find(moves.begin(), moves.end(), destination) != moves.end();
}

std::vector<Position> Rules::getNormalMoves(const GameState& state, Player player) const {
    Position current = state.getPlayerPosition(player);
    Position opponent = state.getPlayerPosition(opponentOf(player));

    std::vector<Position> result;
    for (const auto& next : board.getNeighborsIgnoringPawns(current, state.getPlacedWalls())) {
        if (next != opponent) {
            result.push_back(next);
        }
    }
    return result;
}

std::vector<Position> Rules::getJumpMoves(const GameState& state, Player player) const {
    Position current = state.getPlayerPosition(player);
    Position opponent = state.getPlayerPosition(opponentOf(player));

    if (board.isEdgeBlocked(current, opponent, state.getPlacedWalls())) {
        return {};
    }

    int dRow = opponent.row - current.row;
    int dCol = opponent.col - current.col;
    if (std::abs(dRow) + std::abs(dCol) != 1) {
        return {};
    }

    Position jump{opponent.row + dRow, opponent.col + dCol};
    if (board.isInsideBoard(jump) && !board.isEdgeBlocked(opponent, jump, state.getPlacedWalls())) {
        return {jump};
    }
    return {};
}

std::vector<Position> Rules::getDiagonalMovesAroundOpponent(const GameState& state, Player player) const {
    Position current = state.getPlayerPosition(player);
    Position opponent = state.getPlayerPosition(opponentOf(player));

    if (board.isEdgeBlocked(current, opponent, state.getPlacedWalls())) {
        return {};
    }

    int dRow = opponent.row - current.row;
    int dCol = opponent.col - current.col;
    if (std::abs(dRow) + std::abs(dCol) != 1) {
        return {};
    }

    Position behind{opponent.row + dRow, opponent.col + dCol};
    bool jumpBlocked = !board.isInsideBoard(behind) || board.isEdgeBlocked(opponent, behind, state.getPlacedWalls());
    if (!jumpBlocked) {
        return {};
    }

    std::vector<Position> result;
    for (const auto& candidate : board.getNeighborsIgnoringPawns(opponent, state.getPlacedWalls())) {
        if (candidate != current && candidate != behind) {
            result.push_back(candidate);
        }
    }
    return result;
}

bool Rules::isLegalWallPlacement(const GameState& state, const Wall& wall) const {
    Player player = state.getCurrentPlayer();
    if (state.getWallsRemaining(player) <= 0) {
        return false;
    }
    return wallIsInsideBoard(wall)
        && !wallOverlapsExistingWall(wall, state.getPlacedWalls())
        && !wallCrossesExistingWall(wall, state.getPlacedWalls())
        && wallPreservesPaths(state, wall);
}

bool Rules::wallIsInsideBoard(const Wall& wall) const {
    return wall.row >= 0 && wall.row < board.getSize() - 1
        && wall.col >= 0 && wall.col < board.getSize() - 1;
}

bool Rules::wallOverlapsExistingWall(const Wall& wall, const std::set<Wall>& existingWalls) const {
    return existingWalls.find(wall) != existingWalls.end();
}

bool Rules::wallCrossesExistingWall(const Wall& wall, const std::set<Wall>& existingWalls) const {
    Wall opposite{wall.row, wall.col,
        wall.orientation == WallOrientation::Horizontal ? WallOrientation::Vertical : WallOrientation::Horizontal};
    return existingWalls.find(opposite) != existingWalls.end();
}

bool Rules::wallPreservesPaths(const GameState& state, const Wall& wall) const {
    std::set<Wall> walls = state.getPlacedWalls();
    walls.insert(wall);

    return Search::bfsPathExists(board, state.getPlayerPosition(Player::Player1), getGoalRow(Player::Player1), walls)
        && Search::bfsPathExists(board, state.getPlayerPosition(Player::Player2), getGoalRow(Player::Player2), walls);
}

std::optional<Player> Rules::checkWinner(const GameState& state) const {
    if (state.getPlayerPosition(Player::Player1).row == getGoalRow(Player::Player1)) {
        return Player::Player1;
    }
    if (state.getPlayerPosition(Player::Player2).row == getGoalRow(Player::Player2)) {
        return Player::Player2;
    }
    return std::nullopt;
}

int Rules::getGoalRow(Player player) const {
    return player == Player::Player1 ? Constants::PLAYER_1_GOAL_ROW : Constants::PLAYER_2_GOAL_ROW;
}

} // namespace quoridor
