#include "ChessOptions.h"

ChessOptions::ChessOptions() : type(ChessPiece::none), size(19), number(2) {}

ChessOptions::~ChessOptions() = default;

GomokuOptions::GomokuOptions() : mode(Mode::FRIEND) {};
