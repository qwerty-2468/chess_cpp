#include <iostream>
#include "piece.hpp"
#include "spot.hpp"
#include "board.hpp"
#include "pieces.hpp"
#include "game.hpp"

void Spot::setXY(int X, int Y){ x=X; y=Y; }

int Spot::getRow(){ return x; }

int Spot::getCol(){ return y; }

void Spot::setPiece(Piece* p) { piece=p; }

Piece* Spot::getPiece() const { return piece; }

bool Spot::isEmpty() const { return (piece == nullptr); }
