#ifndef PIECES_HPP_INCLUDED
#define PIECES_HPP_INCLUDED
//#include "memtrace.h"

class Pawn : public Piece {
public:
    Pawn(Color color) : Piece(color) {}
    Piece* clone() const { return new Pawn(*this); }
    char getSymbol() const { return 'P'; }
    bool specificValidation(Spot* currentSpot, Spot* destinationSpot) const;
};

class King : public Piece {
public:
    King(Color color) : Piece(color) {}
    Piece* clone() const { return new King(*this); }
    char getSymbol() const { return 'K'; }
    bool specificValidation(Spot* currentSpot, Spot* destinationSpot) const;
};

class Queen :public Piece{
public:
    Queen(Color color) : Piece(color) {}
    Piece* clone() const { return new Queen(*this); }
    char getSymbol() const { return 'Q'; }
    bool specificValidation(Spot* currentSpot, Spot* destinationSpot) const;
};

class Rook : public Piece {
public:
    Rook(Color color=Color::WHITE) : Piece(color) {}
    Piece* clone() const { return new Rook(*this); }
    char getSymbol() const { return 'R'; }
    bool specificValidation(Spot* currentSpot, Spot* destinationSpot) const;
};

class Knight :public Piece{
public:
    Knight(Color color) : Piece(color) {}
    Piece* clone() const { return new Knight(*this); }
    char getSymbol() const { return 'N'; }
    bool specificValidation(Spot* currentSpot, Spot* destinationSpot) const;
};

class Bishop :public Piece{
public:
    Bishop(Color color) : Piece(color) {}
    Piece* clone() const { return new Bishop(*this); }
    char getSymbol() const { return 'B'; }
    bool specificValidation(Spot* currentSpot, Spot* destinationSpot) const;
};

#endif // PIECES_HPP_INCLUDED
