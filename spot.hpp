#ifndef SPOT_HPP_INCLUDED
#define SPOT_HPP_INCLUDED

class Spot{
    int x,y;
    Piece* piece;
public:
    Spot(int x=0, int y=0, Piece* p=nullptr):x(x),y(y),piece(p){}
    ~Spot(){ delete piece; }
    void setXY(int X, int Y);
    int getRow();
    int getCol();
    void setPiece(Piece* p);
    Piece* getPiece() const;
    bool isEmpty() const;
};

#endif // SPOT_HPP_INCLUDED
