#ifndef RULES_HPP
#define RULES_HPP

#include "Board.hpp"
#include "GameState.hpp"
#include "Types.hpp"

#include <optional>
#include <set>
#include <vector>

namespace quoridor {

class Rules {
private:
    const Board& board;

public:
    explicit Rules(const Board& boardRef);

    std::vector<Position> getLegalPawnMoves(const GameState& state, Player player) const;
    bool isLegalPawnMove(const GameState& state, Player player, Position destination) const;

    std::vector<Position> getNormalMoves(const GameState& state, Player player) const;
    std::vector<Position> getJumpMoves(const GameState& state, Player player) const;
    std::vector<Position> getDiagonalMovesAroundOpponent(const GameState& state, Player player) const;

    bool isLegalWallPlacement(const GameState& state, const Wall& wall) const;
    bool wallIsInsideBoard(const Wall& wall) const;
    bool wallOverlapsExistingWall(const Wall& wall, const std::set<Wall>& existingWalls) const;
    bool wallCrossesExistingWall(const Wall& wall, const std::set<Wall>& existingWalls) const;
    bool wallPreservesPaths(const GameState& state, const Wall& wall) const;

    std::optional<Player> checkWinner(const GameState& state) const;
    int getGoalRow(Player player) const;
};

} // namespace quoridor

#endif
