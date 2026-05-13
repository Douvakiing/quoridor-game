#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "Constants.hpp"
#include "Types.hpp"

#include <optional>
#include <set>

namespace quoridor {

class GameState {
private:
    Position player1Position{Constants::PLAYER_1_START};
    Position player2Position{Constants::PLAYER_2_START};
    int player1Walls{Constants::WALLS_PER_PLAYER};
    int player2Walls{Constants::WALLS_PER_PLAYER};
    std::set<Wall> placedWalls;
    Player currentPlayer{Player::Player1};
    std::optional<Player> winner;

public:
    GameState() = default;

    Position getPlayerPosition(Player player) const;
    void setPlayerPosition(Player player, Position position);

    int getWallsRemaining(Player player) const;
    void decrementWalls(Player player);

    const std::set<Wall>& getPlacedWalls() const;
    void addWall(const Wall& wall);

    Player getCurrentPlayer() const;
    void setCurrentPlayer(Player player);
    Player getOpponent(Player player) const;
    void switchTurn();

    std::optional<Player> getWinner() const;
    void setWinner(Player player);
    void clearWinner();

    bool isGameOver() const;
    GameState clone() const;
};

} // namespace quoridor

#endif
