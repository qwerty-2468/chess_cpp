#ifndef PIECE_HPP_INCLUDED
#define PIECE_HPP_INCLUDED

// Forward declarations
class Board;
class Spot;

// Enum for piece colors
enum class Color { WHITE, BLACK };


// Base class for all pieces
class Piece
{
private:
    Color color;
public:
    Piece(Color color) : color(color) {}
    virtual ~Piece() {}
    virtual char getSymbol() const = 0;
    Color getColor() const;
    void move(Board& board);
    bool isMoveResolvingCheck(const Board& board, Spot* currentSpot, Spot* destinationSpot) const;
    bool commonValidation(const Board& board, Spot* currentSpot, Spot* destinationSpot) const;
    bool enPassantValidation(const Board& board, Spot* currentSpot, Spot* destinationSpot) const;
    virtual bool specificValidation(Spot* currentSpot, Spot* destinationSpot) const = 0;
    Spot* getCurrentSpot(const Board& board) const;
    Spot** getPossibleMoves(const Board& board) const;
    void addMoveToArray(Spot**& possibleMoves, Spot* destinationSpot) const;
    bool isPathObstructed(const Board& board, Spot* currentSpot, Spot* destinationSpot) const;
    virtual Piece* clone() const = 0;
};

#endif // PIECE_HPP_INCLUDED
