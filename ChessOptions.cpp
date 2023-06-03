#include "ChessOptions.h"

ChessOptions::ChessOptions() : number(2), type(ChessPiece::none), size(19) {}

ChessOptions::~ChessOptions() = default;

GomokuOptions::GomokuOptions() : mode(Mode::FRIEND) {};
