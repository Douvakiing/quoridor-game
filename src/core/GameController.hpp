#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "Board.hpp"
#include "GameState.hpp"
#include "Rules.hpp"
#include "Types.hpp"

#include <string>
#include <vector>

namespace quoridor {

enum class GameMode {
    HumanVsHuman,
    HumanVsComputer
};

class GameController {
private:
    Board board;
    GameState state;
    Rules rules;
    GameMode mode;
    std::string message;

public:
    explicit GameController(GameMode gameMode = GameMode::HumanVsHuman);

    void resetGame();

    const GameState& getState() const;
    const Board& getBoard() const;
    const Rules& getRules() const;

    bool movePawn(Position destination);
    bool placeWall(const Wall& wall);
    bool applyMove(const Move& move);

    void endTurn();
    void updateWinner();

    std::vector<Move> getLegalMovesForCurrentPlayer() const;

    bool shouldAIMove() const;
    void makeAIMove();

    std::string getMessage() const;
    void setMessage(const std::string& newMessage);
};

} // namespace quoridor

#endif
