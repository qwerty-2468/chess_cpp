#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "piece.hpp"
#include "spot.hpp"
#include "board.hpp"
#include "pieces.hpp"
#include "game.hpp"

void Board::initializePieces()
{
    // Place white pieces
    placePiece(0, 0, new Rook(Color::WHITE));
    placePiece(0, 1, new Knight(Color::WHITE));
    placePiece(0, 2, new Bishop(Color::WHITE));
    placePiece(0, 3, new Queen(Color::WHITE));
    placePiece(0, 4, new King(Color::WHITE));
    placePiece(0, 5, new Bishop(Color::WHITE));
    placePiece(0, 6, new Knight(Color::WHITE));
    placePiece(0, 7, new Rook(Color::WHITE));
    for (int i = 0; i < 8; i++)
    {
        placePiece(1, i, new Pawn(Color::WHITE));
    }

    //Place black pieces
    placePiece(7, 0, new Rook(Color::BLACK));
    placePiece(7, 1, new Knight(Color::BLACK));
    placePiece(7, 2, new Bishop(Color::BLACK));
    placePiece(7, 3, new Queen(Color::BLACK));
    placePiece(7, 4, new King(Color::BLACK));
    placePiece(7, 5, new Bishop(Color::BLACK));
    placePiece(7, 6, new Knight(Color::BLACK));
    placePiece(7, 7, new Rook(Color::BLACK));
    for (int i = 0; i < 8; i++)
    {
        placePiece(6, i, new Pawn(Color::BLACK));
    }
}

Spot* Board::getKingSpot(Color color) const
{
    Spot* kingSpot = nullptr;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Piece* piece = fields[i][j]->getPiece();
            if (piece != nullptr && piece->getSymbol() == 'K' && piece->getColor() == color)
            {
                kingSpot = fields[i][j];
                break;
            }
        }
        if (kingSpot != nullptr)
        {
            break;
        }
    }
    return kingSpot;
}

bool Board::isKingSafe(Color color)
{
    // Find the king of the given color
    Spot* kingSpot = getKingSpot(color);

#ifdef DEBUG
    // For safety but the King have to be on the Board
    if (kingSpot == nullptr)
    {
        std::cout<<"king_not_found"<<std::endl;;
        return true;
    }
#endif // DEBUG

    // Check if any opponent piece can attack the king's spot
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Piece* piece = fields[i][j]->getPiece();
            if (piece != nullptr && piece->getColor() != color)
            {
                if (piece->commonValidation(*this, fields[i][j], kingSpot))
                {
                    // The king is under attack, not safe
                    return false;
                }
            }
        }
    }

    // King is safe
    return true;
}

bool Board::isCheckmate(Color color)
{
    // This function checks for stalemate as well

    // Check if there are any legal moves available (all moves are checked for resolving the check)
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Piece* piece = fields[i][j]->getPiece();
            if (piece != nullptr && piece->getColor() == color)
            {
                Spot** possibleMoves = piece->getPossibleMoves(*this);
                if(possibleMoves[0] != nullptr)
                {
#ifdef DEBUG
                    std::cout<<i<<" "<<j<<std::endl;
                    std::cout<<possibleMoves[0]->getRow()<<" "<<possibleMoves[0]->getCol()<<std::endl;
#endif // DEBUG
                    delete[] possibleMoves;
                    return false;
                }
                delete[] possibleMoves;

            }
        }
    }
    // No legal moves available, it's checkmate or stalemate
    return true;
}

Board::Board() :captureCountWhite(0), capturedWhite(new Piece*[0]), captureCountBlack(0), capturedBlack(new Piece*[0]), enPassantTarget(nullptr)
{
    for(int x=0; x<8; x++)
    {
        for(int y=0; y<8; y++)
        {
            fields[x][y]=new Spot(x,y);
        }
    }
    initializePieces();
}

Board::Board(const Board& board) :captureCountWhite(board.captureCountWhite), capturedWhite(new Piece*[board.captureCountWhite]), captureCountBlack(board.captureCountBlack), capturedBlack(new Piece*[board.captureCountBlack]), enPassantTarget(board.enPassantTarget)
{
    for(int x=0; x<8; x++)
    {
        for(int y=0; y<8; y++)
        {
            fields[x][y]=new Spot(x,y);
        }
    }
    for(int x=0; x<8; x++)
    {
        for(int y=0; y<8; y++)
        {
            if(board.fields[x][y]->getPiece() != nullptr)
            {
                fields[x][y]->setPiece(board.fields[x][y]->getPiece()->clone());
            }
        }
    }
    for(int i=0; i<captureCountWhite; i++)
    {
        capturedWhite[i] = board.capturedWhite[i]->clone();
    }
    for(int i=0; i<captureCountBlack; i++)
    {
        capturedBlack[i] = board.capturedBlack[i]->clone();
    }
}

Board::~Board()
{
#ifdef DEBUG
    std::cout<<"Board_dtor"<<std::endl;
#endif // DEBUG

    for(int x=0; x<8; x++)
    {
        for(int y=0; y<8; y++)
        {
            delete fields[x][y];
        }
    }

    for(int i=0; i<captureCountWhite; i++)
    {
        delete capturedWhite[i];
    }
    delete[] capturedWhite;
    for(int i=0; i<captureCountBlack; i++)
    {
        delete capturedBlack[i];
    }
    delete[] capturedBlack;
}

void Board::placePiece(int x, int y, Piece* piece)
{
    fields[x][y]->setPiece(piece);
}

void Board::movePiece(Spot* start, Spot* end)
{
    // Dealing with en passant move and taking care of target spot
    enPassant(start, end);

    // Capture piece
    if(!(end->isEmpty()))
    {
        capturePiece(end->getRow(), end->getCol());
    }

    // Move piece
    end->setPiece(start->getPiece());
    start->setPiece(nullptr);

    // Pawn promotion
    pawnPromotion(end);
}

void Board::enPassant(Spot* start, Spot* end)
{
    // If it was en passant move capture piece
    if(end == enPassantTarget)
    {
        capturePiece(start->getRow(), enPassantTarget->getCol());
    }

    // Set target spot for en passant if applicable
    if(start->getPiece()->getSymbol() == 'P' && std::abs(start->getRow() - end->getRow()) == 2)
    {
        enPassantTarget = getSpot(start->getRow() + 1, start->getCol());
    }
    else
    {
        // Set to nullptr if not applicable
        enPassantTarget = nullptr;
    }
}

void Board::pawnPromotion(Spot* end)
{
    srand(time(NULL));
    if(end->getPiece()->getSymbol() == 'P' && end->getRow() == 7 && captureCountWhite > 0)
    {
        // Generate random number for choosing piece
        int index = rand() % captureCountWhite;

        Piece* capturedPiece = capturedWhite[index];
        capturedWhite[index] = end->getPiece();
        end->setPiece(capturedPiece);
    }
    else if(end->getPiece()->getSymbol() == 'P' && end->getRow() == 0 && captureCountBlack > 0)
    {
        // Generate random number for choosing piece
        int index = rand() % captureCountBlack;

        Piece* capturedPiece = capturedBlack[index];
        capturedBlack[index] = end->getPiece();
        end->setPiece(capturedPiece);
    }
}

void Board::capturePiece(int x, int y)
{
    if(!(getSpot(x,y)->isEmpty()))
    {
        Color color = getSpot(x,y)->getPiece()->getColor();
        int& captureCount = (color == Color::WHITE) ? captureCountWhite : captureCountBlack;
        Piece**& captured = (color == Color::WHITE) ? capturedWhite : capturedBlack;

        Piece** newCaptured = new Piece*[captureCount+1];
        for(int i=0; i<captureCount; i++)
        {
            newCaptured[i]=captured[i];
        }
        newCaptured[captureCount++]=getSpot(x,y)->getPiece();
        delete[] captured;
        captured=newCaptured;
        getSpot(x,y)->setPiece(nullptr);
    }
}

Spot* Board::getSpot(int x, int y) const
{
    if(x>=0 && x<=7 && y>=0 && y<=7)
    {
        return fields[x][y];
    }
    std::cout<<"out_of_range"<<std::endl;
    return nullptr;
}

Spot* Board::getEnPassantTarget() const
{
    return enPassantTarget;
}

void Board::clear()
{
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            Piece* piece = fields[x][y]->getPiece();
            if(piece != nullptr && piece->getSymbol() != 'K')
            {
                delete fields[x][y]->getPiece();
                fields[x][y]->setPiece(nullptr);
            }
        }
    }
}

void Board::display() const
{
#ifndef CPORTA
#ifndef DEBUG
#ifdef WIN32
    system("cls");
#endif // WIN32
#endif // DEBUG
#endif // CPORTA
    std::cout<<"    a b c d e f g h"<<std::endl;
    std::cout<<"   -----------------"<<std::endl;
    for (int i = 0; i < 8; i++)
    {
        std::cout << i+1 << " | ";
        for (int j = 0; j < 8; j++)
        {
            if (fields[i][j]->isEmpty())
            {
                std::cout << "- ";
            }
            else
            {
                char symbol = fields[i][j]->getPiece()->getSymbol();
                symbol = fields[i][j]->getPiece()->getColor() == Color::WHITE ? symbol : tolower(symbol);
                std::cout << symbol << " ";
            }
        }
        std::cout << "| " << i+1 << std::endl;
    }
    std::cout<<"   -----------------"<<std::endl;
    std::cout << "    a b c d e f g h" << std::endl;
}
