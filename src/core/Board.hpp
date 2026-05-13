#ifndef BOARD_HPP
#define BOARD_HPP

#include "Types.hpp"

#include <set>
#include <vector>

namespace quoridor {

class Board {
private:
    int size;

public:
    explicit Board(int boardSize = 9);

    int getSize() const;
    bool isInsideBoard(Position position) const;

    std::vector<Position> getBasicNeighbors(Position position) const;

    std::set<Edge> wallToBlockedEdges(const Wall& wall) const;
    std::set<Edge> getBlockedEdges(const std::set<Wall>& walls) const;

    bool isEdgeBlocked(Position from, Position to, const std::set<Wall>& walls) const;

    std::vector<Position> getNeighborsIgnoringPawns(
        Position position,
        const std::set<Wall>& walls
    ) const;
};

} // namespace quoridor

#endif
