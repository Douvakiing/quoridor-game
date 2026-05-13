#include "Board.hpp"

namespace quoridor {

Board::Board(int boardSize) : size(boardSize) {}

int Board::getSize() const {
    return size;
}

bool Board::isInsideBoard(Position position) const {
    return position.row >= 0 && position.row < size && position.col >= 0 && position.col < size;
}

std::vector<Position> Board::getBasicNeighbors(Position position) const {
    std::vector<Position> candidates{
        {position.row - 1, position.col},
        {position.row + 1, position.col},
        {position.row, position.col - 1},
        {position.row, position.col + 1}
    };

    std::vector<Position> result;
    for (const auto& candidate : candidates) {
        if (isInsideBoard(candidate)) {
            result.push_back(candidate);
        }
    }
    return result;
}

std::set<Edge> Board::wallToBlockedEdges(const Wall& wall) const {
    std::set<Edge> edges;

    if (wall.orientation == WallOrientation::Horizontal) {
        edges.insert(Edge({wall.row, wall.col}, {wall.row + 1, wall.col}));
        edges.insert(Edge({wall.row, wall.col + 1}, {wall.row + 1, wall.col + 1}));
    } else {
        edges.insert(Edge({wall.row, wall.col}, {wall.row, wall.col + 1}));
        edges.insert(Edge({wall.row + 1, wall.col}, {wall.row + 1, wall.col + 1}));
    }

    return edges;
}

std::set<Edge> Board::getBlockedEdges(const std::set<Wall>& walls) const {
    std::set<Edge> blocked;
    for (const auto& wall : walls) {
        auto wallEdges = wallToBlockedEdges(wall);
        blocked.insert(wallEdges.begin(), wallEdges.end());
    }
    return blocked;
}

bool Board::isEdgeBlocked(Position from, Position to, const std::set<Wall>& walls) const {
    const auto blocked = getBlockedEdges(walls);
    return blocked.find(Edge(from, to)) != blocked.end();
}

std::vector<Position> Board::getNeighborsIgnoringPawns(
    Position position,
    const std::set<Wall>& walls
) const {
    std::vector<Position> result;
    for (const auto& neighbor : getBasicNeighbors(position)) {
        if (!isEdgeBlocked(position, neighbor, walls)) {
            result.push_back(neighbor);
        }
    }
    return result;
}

} // namespace quoridor
