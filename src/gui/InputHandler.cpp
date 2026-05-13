#include "gui/InputHandler.hpp"

namespace quoridor {

std::optional<Position> InputHandler::screenToBoardPosition(int x, int y) const {
    // Placeholder conversion for a future GUI. For now, x=row and y=col.
    return Position{x, y};
}

std::optional<Wall> InputHandler::screenToWallPosition(int x, int y) const {
    // Placeholder conversion for a future GUI. For now, x=row and y=col.
    return Wall{x, y, currentWallOrientation};
}

void InputHandler::toggleWallOrientation() {
    currentWallOrientation = currentWallOrientation == WallOrientation::Horizontal
        ? WallOrientation::Vertical
        : WallOrientation::Horizontal;
}

WallOrientation InputHandler::getCurrentWallOrientation() const {
    return currentWallOrientation;
}

} // namespace quoridor
