#ifndef BOARD_HPP_INCLUDED
#define BOARD_HPP_INCLUDED

#include <cstdlib>
#include <typeinfo>

class Board{
    Spot* fields[8][8];
    int captureCountWhite;
    Piece** capturedWhite;
    int captureCountBlack;
    Piece** capturedBlack;
    Spot* enPassantTarget;
public:
    Board();
    Board(const Board& board);
    ~Board();
    void initializePieces();
    Spot* getKingSpot(Color color) const;
    void placePiece(int x, int y, Piece* piece);
    void movePiece(Spot* start, Spot* end);
    void enPassant(Spot* start, Spot* end);
    void pawnPromotion(Spot* end);
    void capturePiece(int x, int y);
    bool isKingSafe(Color color);
    bool isCheckmate(Color color);
    Spot* getSpot(int x, int y) const;
    Spot* getEnPassantTarget() const;
    void clear();
    void display() const;
};


#endif // BOARD_HPP_INCLUDED
