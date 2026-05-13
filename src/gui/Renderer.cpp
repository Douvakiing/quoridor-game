#include "gui/Renderer.hpp"

#include <iostream>

namespace quoridor {

void Renderer::clear() {
    std::cout << "\n";
}

void Renderer::drawBoard(const Board& board) {
    std::cout << "Quoridor board: " << board.getSize() << "x" << board.getSize() << "\n";
}

void Renderer::drawPawns(const GameState& state) {
    auto p1 = state.getPlayerPosition(Player::Player1);
    auto p2 = state.getPlayerPosition(Player::Player2);
    std::cout << "P1: (" << p1.row << ", " << p1.col << ")  ";
    std::cout << "P2: (" << p2.row << ", " << p2.col << ")\n";
}

void Renderer::drawWalls(const GameState& state) {
    std::cout << "Placed walls: " << state.getPlacedWalls().size() << "\n";
}

void Renderer::drawValidMoveHighlights(const std::vector<Position>& moves) {
    std::cout << "Legal pawn moves: ";
    for (const auto& move : moves) {
        std::cout << "(" << move.row << "," << move.col << ") ";
    }
    std::cout << "\n";
}

void Renderer::drawWallPreview(const Wall& wall, bool isValid) {
    std::cout << "Wall preview at (" << wall.row << "," << wall.col << ") "
              << (wall.orientation == WallOrientation::Horizontal ? "H" : "V")
              << (isValid ? " valid" : " invalid") << "\n";
}

void Renderer::drawTurnIndicator(const GameState& state) {
    std::cout << (state.getCurrentPlayer() == Player::Player1 ? "Player 1" : "Player 2") << " to move\n";
}

void Renderer::drawWallCounts(const GameState& state) {
    std::cout << "Walls - P1: " << state.getWallsRemaining(Player::Player1)
              << ", P2: " << state.getWallsRemaining(Player::Player2) << "\n";
}

void Renderer::drawMessage(const std::string& message) {
    std::cout << message << "\n";
}

void Renderer::display() {}

} // namespace quoridor
