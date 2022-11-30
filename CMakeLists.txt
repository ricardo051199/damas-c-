cmake_minimum_required(VERSION 3.23)
project(proyecto_final)

set(CMAKE_CXX_STANDARD 14)

add_executable(proyecto_final main.cpp Colour.h Controller.cpp Controller.h GameBoard.cpp GameBoard.h GameError.h GameMode.h GameUI.cpp GameUI.h Move.cpp Move.h Piece.cpp Piece.h PieceType.h Player.cpp Player.h PlayerAI.cpp PlayerAI.h PlayerHuman.cpp PlayerHuman.h)
