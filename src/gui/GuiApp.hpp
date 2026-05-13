#ifndef GUI_APP_HPP
#define GUI_APP_HPP

#include "core/GameController.hpp"
#include "gui/InputHandler.hpp"
#include "gui/Renderer.hpp"

namespace quoridor {

class GuiApp {
private:
    GameController controller;
    Renderer renderer;
    InputHandler inputHandler;
    bool running{true};

public:
    GuiApp();
    void run();

private:
    void handleEvents();
    void update();
    void draw();
    void reset();
};

} // namespace quoridor

#endif
