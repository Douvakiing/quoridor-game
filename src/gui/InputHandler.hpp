#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include "core/Types.hpp"

#include <optional>

namespace quoridor {

class InputHandler {
private:
    WallOrientation currentWallOrientation{WallOrientation::Horizontal};

public:
    InputHandler() = default;

    std::optional<Position> screenToBoardPosition(int x, int y) const;
    std::optional<Wall> screenToWallPosition(int x, int y) const;
    void toggleWallOrientation();
    WallOrientation getCurrentWallOrientation() const;
};

} // namespace quoridor

#endif
