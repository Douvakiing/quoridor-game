#include "core/GameController.hpp"
#include "ai/GreedyAI.hpp"

namespace quoridor {

GameController::GameController(GameMode gameMode)
    : board(Constants::BOARD_SIZE), state(), rules(board), mode(gameMode), message("Player 1 turn") {}

void GameController::resetGame() {
    state = GameState();
    message = "Game reset. Player 1 turn";
}

const GameState& GameController::getState() const { return state; }
const Board& GameController::getBoard() const { return board; }
const Rules& GameController::getRules() const { return rules; }

bool GameController::movePawn(Position destination) {
    Player player = state.getCurrentPlayer();
    if (!rules.isLegalPawnMove(state, player, destination)) {
        message = "Invalid pawn move";
        return false;
    }

    state.setPlayerPosition(player, destination);
    updateWinner();
    if (!state.isGameOver()) {
        endTurn();
    }
    return true;
}

bool GameController::placeWall(const Wall& wall) {
    Player player = state.getCurrentPlayer();
    if (!rules.isLegalWallPlacement(state, wall)) {
        message = "Invalid wall placement";
        return false;
    }

    state.addWall(wall);
    state.decrementWalls(player);
    endTurn();
    return true;
}

bool GameController::applyMove(const Move& move) {
    if (move.type == MoveType::PawnMove && move.destination.has_value()) {
        return movePawn(move.destination.value());
    }
    if (move.type == MoveType::WallPlacement && move.wall.has_value()) {
        return placeWall(move.wall.value());
    }
    message = "Invalid move object";
    return false;
}

void GameController::endTurn() {
    state.switchTurn();
    message = state.getCurrentPlayer() == Player::Player1 ? "Player 1 turn" : "Player 2 turn";
}

void GameController::updateWinner() {
    auto winner = rules.checkWinner(state);
    if (winner.has_value()) {
        state.setWinner(winner.value());
        message = winner.value() == Player::Player1 ? "Player 1 wins" : "Player 2 wins";
    }
}

std::vector<Move> GameController::getLegalMovesForCurrentPlayer() const {
    std::vector<Move> moves;
    Player player = state.getCurrentPlayer();
    for (const auto& position : rules.getLegalPawnMoves(state, player)) {
        moves.push_back(Move::pawnMove(position));
    }
    return moves;
}

bool GameController::shouldAIMove() const {
    return mode == GameMode::HumanVsComputer && state.getCurrentPlayer() == Player::Player2 && !state.isGameOver();
}

void GameController::makeAIMove() {
    if (!shouldAIMove()) {
        return;
    }
    GreedyAI ai(Player::Player2, board, rules);
    applyMove(ai.chooseMove(state));
}

std::string GameController::getMessage() const { return message; }
void GameController::setMessage(const std::string& newMessage) { message = newMessage; }

} // namespace quoridor
