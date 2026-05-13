cmake_minimum_required(VERSION 3.19)
project(quoridor-game LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(quoridor-game
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    src/core/Types.cpp
    src/core/GameState.cpp
    src/core/Board.cpp
    src/core/Search.cpp
    src/core/Rules.cpp
    src/core/GameController.cpp

    src/ai/Evaluation.cpp
    src/ai/GreedyAI.cpp
    src/ai/MoveOrdering.cpp
    src/ai/MinimaxAI.cpp

    src/gui/Renderer.cpp
    src/gui/InputHandler.cpp
    src/gui/GuiApp.cpp

    src/core/Types.hpp
    src/core/GameState.hpp
    src/core/Board.hpp
    src/core/Search.hpp
    src/core/Rules.hpp
    src/core/GameController.hpp

    src/ai/Evaluation.hpp
    src/ai/GreedyAI.hpp
    src/ai/MoveOrdering.hpp
    src/ai/MinimaxAI.hpp

    src/gui/Renderer.hpp
    src/gui/InputHandler.hpp
    src/gui/GuiApp.hpp

    src/gameEngine.cpp src/gameEngine.h
    GuiApp.ui
)

target_link_libraries(quoridor-game
    PRIVATE
        Qt::Core
        Qt::Widgets
)

target_include_directories(quoridor-game
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

install(TARGETS quoridor-game
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET quoridor-game
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
