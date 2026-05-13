#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "core/Board.hpp"
#include "core/GameState.hpp"
#include "core/Types.hpp"

#include <string>
#include <vector>

namespace quoridor {

class Renderer {
public:
    Renderer() = default;

    void clear();
    void drawBoard(const Board& board);
    void drawPawns(const GameState& state);
    void drawWalls(const GameState& state);
    void drawValidMoveHighlights(const std::vector<Position>& moves);
    void drawWallPreview(const Wall& wall, bool isValid);
    void drawTurnIndicator(const GameState& state);
    void drawWallCounts(const GameState& state);
    void drawMessage(const std::string& message);
    void display();
};

} // namespace quoridor

#endif
