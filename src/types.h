#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>
#include <set>
#include <optional>
#include <string>

enum class Player {
    Player1,
    Player2
};

enum class WallOrientation {
    Horizontal,
    Vertical
};

enum class MoveType {
    PawnMove,
    WallPlacement
};

struct Position {
    int row;
    int col;

    bool operator==(const Position& other) const;
    bool operator<(const Position& other) const;
};

struct Wall {
    int row;
    int col;
    WallOrientation orientation;

    bool operator==(const Wall& other) const;
    bool operator<(const Wall& other) const;
};

struct Edge {
    Position a;
    Position b;

    Edge(Position p1, Position p2);

    bool operator==(const Edge& other) const;
    bool operator<(const Edge& other) const;
};

struct Move {
    MoveType type;
    std::optional<Position> destination;
    std::optional<Wall> wall;
};

#endif