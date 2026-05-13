#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "Board.hpp"
#include "Types.hpp"

#include <map>
#include <optional>
#include <set>
#include <vector>

namespace quoridor::Search {

bool bfsPathExists(
    const Board& board,
    Position start,
    int goalRow,
    const std::set<Wall>& walls
);

int bfsShortestPathLength(
    const Board& board,
    Position start,
    int goalRow,
    const std::set<Wall>& walls
);

std::optional<std::vector<Position>> bfsShortestPath(
    const Board& board,
    Position start,
    int goalRow,
    const std::set<Wall>& walls
);

int heuristicToGoalRow(Position position, int goalRow);

std::optional<std::vector<Position>> astarShortestPath(
    const Board& board,
    Position start,
    int goalRow,
    const std::set<Wall>& walls
);

std::vector<Position> reconstructPath(
    const std::map<Position, Position>& cameFrom,
    Position current
);

} // namespace quoridor::Search

#endif
