#include <iostream>
#include <stdlib.h>
#include "piece.hpp"
#include "spot.hpp"
#include "board.hpp"
#include "pieces.hpp"
#include "game.hpp"

bool Pawn::specificValidation(Spot* currentSpot, Spot* destinationSpot) const
{
    // Pawn-specific validation logic

    int currentRow = currentSpot->getRow();
    int currentCol = currentSpot->getCol();
    int destRow = destinationSpot->getRow();
    int destCol = destinationSpot->getCol();

    // Pawn can move forward by one square, or two squares if it's the first move
    if (getColor() == Color::BLACK)
    {
        if (destRow == currentRow - 1 && destCol == currentCol && destinationSpot->isEmpty())
        {
            return true;
        }
        if (currentRow == 6 && destRow == currentRow - 2 && destCol == currentCol && destinationSpot->isEmpty())
        {
            return true;
        }
        // Pawn can capture diagonally
        if (destRow == currentRow - 1 && (destCol == currentCol - 1 || destCol == currentCol + 1) && !(destinationSpot->isEmpty()))
        {
            return true;
        }
    }
    else
    {
        if (destRow == currentRow + 1 && destCol == currentCol && destinationSpot->isEmpty())
        {
            return true;
        }
        if (currentRow == 1 && destRow == currentRow + 2 && destCol == currentCol && destinationSpot->isEmpty())
        {
            return true;
        }
        // Pawn can capture diagonally
        if (destRow == currentRow + 1 && (destCol == currentCol - 1 || destCol == currentCol + 1) && !(destinationSpot->isEmpty()))
        {
            return true;
        }
    }
    return false;
}

bool King::specificValidation(Spot* currentSpot, Spot* destinationSpot) const
{
    // King-specific validation logic

    int currentRow = currentSpot->getRow();
    int currentCol = currentSpot->getCol();
    int destRow = destinationSpot->getRow();
    int destCol = destinationSpot->getCol();

    // King can move one square in any direction
    int rowDiff = std::abs(destRow - currentRow);
    int colDiff = std::abs(destCol - currentCol);
    if ((rowDiff == 1 && colDiff == 0) || (rowDiff == 0 && colDiff == 1) || (rowDiff == 1 && colDiff == 1))
    {
        return true;
    }

    return false;
}

bool Queen::specificValidation(Spot* currentSpot, Spot* destinationSpot) const
{
    // Queen-specific validation logic

    int currentRow = currentSpot->getRow();
    int currentCol = currentSpot->getCol();
    int destRow = destinationSpot->getRow();
    int destCol = destinationSpot->getCol();

    // Queen can move horizontally, vertically, or diagonally
    int rowDiff = std::abs(destRow - currentRow);
    int colDiff = std::abs(destCol - currentCol);
    if (currentRow == destRow || currentCol == destCol || rowDiff == colDiff)
    {
        return true;
    }

    return false;
}

bool Rook::specificValidation(Spot* currentSpot, Spot* destinationSpot) const
{
    // Rook-specific validation logic

    int currentRow = currentSpot->getRow();
    int currentCol = currentSpot->getCol();
    int destRow = destinationSpot->getRow();
    int destCol = destinationSpot->getCol();

    // Rook can move horizontally or vertically
    if (currentRow == destRow || currentCol == destCol)
    {
        return true;
    }

    return false;
}

bool Knight::specificValidation(Spot* currentSpot, Spot* destinationSpot) const
{
    // Knight-specific validation logic

    int currentRow = currentSpot->getRow();
    int currentCol = currentSpot->getCol();
    int destRow = destinationSpot->getRow();
    int destCol = destinationSpot->getCol();

    // Knight can move in an L-shape: two squares in one direction and one square in the other direction
    int rowDiff = std::abs(destRow - currentRow);
    int colDiff = std::abs(destCol - currentCol);
    if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2))
    {
        return true;
    }

    return false;
}

bool Bishop::specificValidation(Spot* currentSpot, Spot* destinationSpot) const
{
    // Bishop-specific validation logic

    int currentRow = currentSpot->getRow();
    int currentCol = currentSpot->getCol();
    int destRow = destinationSpot->getRow();
    int destCol = destinationSpot->getCol();

    // Bishop can move diagonally
    int rowDiff = std::abs(destRow - currentRow);
    int colDiff = std::abs(destCol - currentCol);
    if (rowDiff == colDiff)
    {
        return true;
    }

    return false;
}
