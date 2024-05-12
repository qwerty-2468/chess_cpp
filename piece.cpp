#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "piece.hpp"
#include "spot.hpp"
#include "board.hpp"
#include "pieces.hpp"
#include "game.hpp"

Color Piece::getColor() const
{
    return color;
}

bool Piece::commonValidation(const Board& board, Spot* currentSpot, Spot* destinationSpot) const
{
    if(currentSpot == destinationSpot)
        return false;

    // Check if the destination spot is within the bounds of the board
    int destRow = destinationSpot->getRow();
    int destCol = destinationSpot->getCol();
    if (destRow < 0 || destRow >= 8 || destCol < 0 || destCol >= 8)
    {
        return false;
    }

    // Check if the destination spot is occupied by a piece of the same color
    Piece* destPiece = destinationSpot->getPiece();
    if (destPiece != nullptr && destPiece->color == color)
    {
        return false;
    }

    // Checking piece specific rules / en passant / castling
    if(!specificValidation(currentSpot, destinationSpot)
            && !enPassantValidation(board, currentSpot, destinationSpot))
    {
        return false;
    }

    // Checking obstacles
    if(getSymbol() != 'N' && isPathObstructed(board, currentSpot, destinationSpot))
        return false;

    // Do not have to check if enemy king is on the spot because of the check checking algorithm

    return true;
}

bool Piece::enPassantValidation(const Board& board, Spot* currentSpot, Spot* destinationSpot) const
{
    // It has to be a pawn
    if(getSymbol() != 'P')
        return false;

    // If no en passant target spot
    if(board.getEnPassantTarget() == nullptr)
        return false;

    int currentRow = currentSpot->getRow();
    int currentCol = currentSpot->getCol();
    int destRow = destinationSpot->getRow();
    int destCol = destinationSpot->getCol();

    int rowDiff = (getColor() == Color::WHITE) ? -1 : 1;
    int startRow = (getColor() == Color::WHITE) ? 5 : 2;

    if (destRow == currentRow - rowDiff && (destCol == currentCol - 1 || destCol == currentCol + 1)
            && (destinationSpot == board.getEnPassantTarget() && board.getEnPassantTarget()->getRow() == startRow))
    {
        return true;
    }

    // Not en passant move
    return false;
}

Spot* Piece::getCurrentSpot(const Board& board) const
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(board.getSpot(i,j)->getPiece()==this)
            {
                return board.getSpot(i,j);
            }
        }
    }
    std::cout<<"bajvan"<<std::endl;
    return nullptr;
}

bool Piece::isMoveResolvingCheck(const Board& board, Spot* currentSpot, Spot* destinationSpot) const
{
    Board tmp(board);
    currentSpot = tmp.getSpot(currentSpot->getRow(), currentSpot->getCol());
    destinationSpot = tmp.getSpot(destinationSpot->getRow(), destinationSpot->getCol());
    delete destinationSpot->getPiece();

    // Make a temporary move to check if it resolves the check
    destinationSpot->setPiece(currentSpot->getPiece());
    currentSpot->setPiece(nullptr);

    // Check if the move resolves the check
    return tmp.isKingSafe(getColor());
}

bool Piece::isPathObstructed(const Board& board, Spot* currentSpot, Spot* destinationSpot) const
{
    // Get the row and column differences between the current and destination spots
    int rowDiff = destinationSpot->getRow() - currentSpot->getRow();
    int colDiff = destinationSpot->getCol() - currentSpot->getCol();

    // Determine the row and column increments based on the differences
    int rowIncrement = (rowDiff > 0) ? 1 : (rowDiff < 0) ? -1 : 0;
    int colIncrement = (colDiff > 0) ? 1 : (colDiff < 0) ? -1 : 0;

    // Iterate over the spots in the path and check for obstacles
    int row = currentSpot->getRow() + rowIncrement;
    int col = currentSpot->getCol() + colIncrement;
    while ((row != destinationSpot->getRow() || col != destinationSpot->getCol()))
    {
#ifdef DEBUG
        if( !(row >= 0 && row <= 7 && col >= 0 && col <= 7) )
        {
            std::cout<<"out_of_range"<<std::endl;
            break;
        }
        std::cout<<row<<" "<<col<<std::endl;
#endif // DEBUG
        Spot* spot = board.getSpot(row, col);
        if (spot->getPiece() != nullptr)
        {
            return true; // Obstacle found in the path
        }
        row += rowIncrement;
        col += colIncrement;
    }

    return false; // No obstacles found
}

Spot** Piece::getPossibleMoves(const Board& board) const
{
    // Get the current spot of the piece
    Spot* currentSpot = getCurrentSpot(board);

    // Create a dynamic array to store the possible moves
    Spot** possibleMoves = new Spot*[1]; // Start with a size of 1
    possibleMoves[0] = nullptr; // Initialize with nullptr

    // Generate the possible moves
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Spot* destinationSpot = board.getSpot(i, j);

            // Validate the move using the commonValidation function
            if (!commonValidation(board, currentSpot, destinationSpot))
                continue;

            // Skip if this move causes unresolved check
            if(!isMoveResolvingCheck(board, currentSpot, destinationSpot))
                continue;

            // If everything is OK add the move
            addMoveToArray(possibleMoves, destinationSpot);
        }
    }
    return possibleMoves;
}

void Piece::addMoveToArray(Spot**& possibleMoves, Spot* destinationSpot) const
{
    // Resize the array to accommodate the new move
    int numMoves = 0;
    while (possibleMoves[numMoves] != nullptr)
    {
        numMoves++;
    }
    Spot** resizedArray = new Spot*[numMoves + 2]; // Increase the size by 1 and add space for nullptr
    for (int k = 0; k < numMoves; k++)
    {
        resizedArray[k] = possibleMoves[k];
    }
    resizedArray[numMoves] = destinationSpot; // Add the new move
    resizedArray[numMoves + 1] = nullptr; // Terminate with nullptr

    // Update the possibleMoves pointer to point to the resized array
    delete[] possibleMoves;
    possibleMoves = resizedArray;
}

void Piece::move(Board& board)
{
    Spot** possibleMoves = getPossibleMoves(board);
    if(possibleMoves[0]!=nullptr)
    {
        // Generate random number for choosing move
        int c = 0;
        while(possibleMoves[c]!=nullptr) c++;
        srand(time(NULL));
        int random_number = rand() % c;

#ifdef DEBUG
        std::cout<<possibleMoves[0]->getCol()<<" "<<possibleMoves[0]->getRow()<<std::endl;
#endif // DEBUG

        // Make the chosen move
        board.movePiece(getCurrentSpot(board), possibleMoves[random_number]);
    }
    else
    {
        delete[] possibleMoves;
        throw "No valid moves for this piece";
    }
    delete[] possibleMoves;
}
