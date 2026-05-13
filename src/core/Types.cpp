#include "core/Types.hpp"

#include <algorithm>
#include <tuple>

namespace quoridor {

bool Position::operator==(const Position& other) const {
    return row == other.row && col == other.col;
}

bool Position::operator!=(const Position& other) const {
    return !(*this == other);
}

bool Position::operator<(const Position& other) const {
    return std::tie(row, col) < std::tie(other.row, other.col);
}

bool Wall::operator==(const Wall& other) const {
    return row == other.row && col == other.col && orientation == other.orientation;
}

bool Wall::operator<(const Wall& other) const {
    return std::tie(row, col, orientation) < std::tie(other.row, other.col, other.orientation);
}

Edge::Edge(Position p1, Position p2) {
    if (p2 < p1) {
        a = p2;
        b = p1;
    } else {
        a = p1;
        b = p2;
    }
}

bool Edge::operator==(const Edge& other) const {
    return a == other.a && b == other.b;
}

bool Edge::operator<(const Edge& other) const {
    return std::tie(a, b) < std::tie(other.a, other.b);
}

Move Move::pawnMove(Position destination) {
    Move move;
    move.type = MoveType::PawnMove;
    move.destination = destination;
    return move;
}

Move Move::wallPlacement(Wall wall) {
    Move move;
    move.type = MoveType::WallPlacement;
    move.wall = wall;
    return move;
}

Player opponentOf(Player player) {
    return player == Player::Player1 ? Player::Player2 : Player::Player1;
}

} // namespace quoridor
