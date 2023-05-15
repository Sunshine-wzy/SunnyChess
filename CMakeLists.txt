cmake_minimum_required(VERSION 3.24)
project(SunnyChess)

set(CMAKE_CXX_STANDARD 11)

link_libraries(libeasyx.a)

add_executable(SunnyChess main.cpp ChessBoard.cpp ChessBoard.h ChessPiece.cpp ChessPiece.h ChessSlot.cpp ChessSlot.h MainMenu.cpp MainMenu.h Button.cpp Button.h RoundRectangleButton.cpp RoundRectangleButton.h Menu.cpp Menu.h GomokuMenu.cpp GomokuMenu.h MenuManager.cpp MenuManager.h Position.h GomokuChessBoard.cpp GomokuChessBoard.h Game.cpp Game.h GomokuPreparationMenu.cpp GomokuPreparationMenu.h SelectionButton.cpp SelectionButton.h CircleSelectionButton.cpp CircleSelectionButton.h SelectionButtonGroup.cpp SelectionButtonGroup.h ChessOptions.cpp ChessOptions.h)
