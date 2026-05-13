#include "GameState.hpp"

namespace quoridor {

Position GameState::getPlayerPosition(Player player) const {
    return player == Player::Player1 ? player1Position : player2Position;
}

void GameState::setPlayerPosition(Player player, Position position) {
    if (player == Player::Player1) {
        player1Position = position;
    } else {
        player2Position = position;
    }
}

int GameState::getWallsRemaining(Player player) const {
    return player == Player::Player1 ? player1Walls : player2Walls;
}

void GameState::decrementWalls(Player player) {
    if (player == Player::Player1 && player1Walls > 0) {
        --player1Walls;
    } else if (player == Player::Player2 && player2Walls > 0) {
        --player2Walls;
    }
}

const std::set<Wall>& GameState::getPlacedWalls() const {
    return placedWalls;
}

void GameState::addWall(const Wall& wall) {
    placedWalls.insert(wall);
}

Player GameState::getCurrentPlayer() const {
    return currentPlayer;
}

void GameState::setCurrentPlayer(Player player) {
    currentPlayer = player;
}

Player GameState::getOpponent(Player player) const {
    return opponentOf(player);
}

void GameState::switchTurn() {
    currentPlayer = opponentOf(currentPlayer);
}

std::optional<Player> GameState::getWinner() const {
    return winner;
}

void GameState::setWinner(Player player) {
    winner = player;
}

void GameState::clearWinner() {
    winner.reset();
}

bool GameState::isGameOver() const {
    return winner.has_value();
}

GameState GameState::clone() const {
    return *this;
}

} // namespace quoridor
