cmake_minimum_required(VERSION 3.24)
project(SunnyChess)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS "-static")
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic")
#set(CMAKE_EXE_LINKER_FLAGS -static)

include_directories(libs/include)
link_directories(libs/lib64)

#link_libraries(gcc stdc++ winpthread libeasyx.a winmm.lib)

add_executable(SunnyChess main.cpp ChessBoard.cpp ChessBoard.h ChessPiece.cpp ChessPiece.h ChessSlot.cpp ChessSlot.h MainMenu.cpp MainMenu.h Button.cpp Button.h RoundRectangleButton.cpp RoundRectangleButton.h Menu.cpp Menu.h GomokuMenu.cpp GomokuMenu.h MenuManager.cpp MenuManager.h Position.h GomokuChessBoard.cpp GomokuChessBoard.h Game.cpp Game.h GomokuPreparationMenu.cpp GomokuPreparationMenu.h SelectionButton.cpp SelectionButton.h CircleSelectionButton.cpp CircleSelectionButton.h SelectionButtonGroup.cpp SelectionButtonGroup.h ChessOptions.cpp ChessOptions.h Direction.cpp Direction.h Player.cpp Player.h Timer.cpp Timer.h DisplayButton.cpp DisplayButton.h)

target_link_libraries(SunnyChess -static gcc stdc++ winpthread libeasyx.a winmm.lib -dynamic)
