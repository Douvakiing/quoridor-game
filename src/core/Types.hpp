#ifndef TYPES_HPP
#define TYPES_HPP

#include <optional>
#include <vector>

namespace quoridor {

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
    int row{};
    int col{};

    bool operator==(const Position& other) const;
    bool operator!=(const Position& other) const;
    bool operator<(const Position& other) const;
};

struct Wall {
    int row{};
    int col{};
    WallOrientation orientation{WallOrientation::Horizontal};

    bool operator==(const Wall& other) const;
    bool operator<(const Wall& other) const;
};

struct Edge {
    Position a;
    Position b;

    Edge() = default;
    Edge(Position p1, Position p2);

    bool operator==(const Edge& other) const;
    bool operator<(const Edge& other) const;
};

struct Move {
    MoveType type{MoveType::PawnMove};
    std::optional<Position> destination;
    std::optional<Wall> wall;

    static Move pawnMove(Position destination);
    static Move wallPlacement(Wall wall);
};

Player opponentOf(Player player);

} // namespace quoridor

#endif
