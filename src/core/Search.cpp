#include "core/Search.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <queue>
#include <tuple>

namespace quoridor::Search {

bool bfsPathExists(
    const Board& board,
    Position start,
    int goalRow,
    const std::set<Wall>& walls
) {
    return bfsShortestPathLength(board, start, goalRow, walls) != std::numeric_limits<int>::max();
}

int bfsShortestPathLength(
    const Board& board,
    Position start,
    int goalRow,
    const std::set<Wall>& walls
) {
    std::queue<std::pair<Position, int>> frontier;
    std::set<Position> visited;

    frontier.push({start, 0});
    visited.insert(start);

    while (!frontier.empty()) {
        auto [current, distance] = frontier.front();
        frontier.pop();

        if (current.row == goalRow) {
            return distance;
        }

        for (const auto& next : board.getNeighborsIgnoringPawns(current, walls)) {
            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                frontier.push({next, distance + 1});
            }
        }
    }

    return std::numeric_limits<int>::max();
}

std::optional<std::vector<Position>> bfsShortestPath(
    const Board& board,
    Position start,
    int goalRow,
    const std::set<Wall>& walls
) {
    std::queue<Position> frontier;
    std::set<Position> visited;
    std::map<Position, Position> cameFrom;

    frontier.push(start);
    visited.insert(start);

    while (!frontier.empty()) {
        Position current = frontier.front();
        frontier.pop();

        if (current.row == goalRow) {
            return reconstructPath(cameFrom, current);
        }

        for (const auto& next : board.getNeighborsIgnoringPawns(current, walls)) {
            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                cameFrom[next] = current;
                frontier.push(next);
            }
        }
    }

    return std::nullopt;
}

int heuristicToGoalRow(Position position, int goalRow) {
    return std::abs(goalRow - position.row);
}

std::optional<std::vector<Position>> astarShortestPath(
    const Board& board,
    Position start,
    int goalRow,
    const std::set<Wall>& walls
) {
    using QueueItem = std::tuple<int, int, Position>; // fScore, gScore, position

    std::priority_queue<QueueItem, std::vector<QueueItem>, std::greater<QueueItem>> openSet;
    std::map<Position, int> gScore;
    std::map<Position, Position> cameFrom;

    gScore[start] = 0;
    openSet.push({heuristicToGoalRow(start, goalRow), 0, start});

    while (!openSet.empty()) {
        auto [currentF, currentG, current] = openSet.top();
        openSet.pop();

        if (current.row == goalRow) {
            return reconstructPath(cameFrom, current);
        }

        if (currentG > gScore[current]) {
            continue;
        }

        for (const auto& next : board.getNeighborsIgnoringPawns(current, walls)) {
            int tentativeG = currentG + 1;
            if (!gScore.count(next) || tentativeG < gScore[next]) {
                cameFrom[next] = current;
                gScore[next] = tentativeG;
                int fScore = tentativeG + heuristicToGoalRow(next, goalRow);
                openSet.push({fScore, tentativeG, next});
            }
        }
    }

    return std::nullopt;
}

std::vector<Position> reconstructPath(
    const std::map<Position, Position>& cameFrom,
    Position current
) {
    std::vector<Position> path{current};
    while (cameFrom.count(current)) {
        current = cameFrom.at(current);
        path.push_back(current);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

} // namespace quoridor::Search
