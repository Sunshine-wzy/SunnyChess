cmake_minimum_required(VERSION 3.24)
project(SunnyChess)

set(CMAKE_CXX_STANDARD 11)

link_libraries(libeasyx.a)

add_executable(SunnyChess main.cpp Chessboard.cpp Chessboard.h ChessPiece.cpp ChessPiece.h ChessSlot.cpp ChessSlot.h)
