#include "gui/GuiApp.hpp"

#include <iostream>
#include <sstream>
#include <string>

namespace quoridor {

GuiApp::GuiApp() : controller(GameMode::HumanVsHuman) {}

void GuiApp::run() {
    std::cout << "Quoridor console scaffold\n";
    std::cout << "Commands: move r c | wall r c H/V | reset | quit\n";

    while (running && !controller.getState().isGameOver()) {
        draw();
        handleEvents();
        update();
    }
    draw();
}

void GuiApp::handleEvents() {
    std::cout << "> ";
    std::string line;
    if (!std::getline(std::cin, line)) {
        running = false;
        return;
    }

    std::istringstream input(line);
    std::string command;
    input >> command;

    if (command == "quit") {
        running = false;
    } else if (command == "reset") {
        reset();
    } else if (command == "move") {
        int row, col;
        if (input >> row >> col) {
            controller.movePawn({row, col});
        }
    } else if (command == "wall") {
        int row, col;
        char orientation;
        if (input >> row >> col >> orientation) {
            controller.placeWall({
                row,
                col,
                orientation == 'V' || orientation == 'v'
                    ? WallOrientation::Vertical
                    : WallOrientation::Horizontal
            });
        }
    } else {
        controller.setMessage("Unknown command");
    }
}

void GuiApp::update() {
    if (controller.shouldAIMove()) {
        controller.makeAIMove();
    }
}

void GuiApp::draw() {
    renderer.clear();
    renderer.drawBoard(controller.getBoard());
    renderer.drawPawns(controller.getState());
    renderer.drawWalls(controller.getState());
    renderer.drawWallCounts(controller.getState());
    renderer.drawTurnIndicator(controller.getState());
    renderer.drawValidMoveHighlights(
        controller.getRules().getLegalPawnMoves(
            controller.getState(),
            controller.getState().getCurrentPlayer()
        )
    );
    renderer.drawMessage(controller.getMessage());
    renderer.display();
}

void GuiApp::reset() {
    controller.resetGame();
}

} // namespace quoridor
