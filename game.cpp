#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "piece.hpp"
#include "spot.hpp"
#include "board.hpp"
#include "pieces.hpp"
#include "game.hpp"

Board& Game::getBoard()
{
    return board;
}

bool Game::getInput(int& row, int& col) const
{
    char c;
    std::cout<<std::endl<<"Quit by 'q1' of EOF"<<std::endl<<"Piece to move by field (like d2): ";
    while( true )
    {
        std::string line;
        std::getline( std::cin, line );
        if(std::cin.eof()) return false;
        std::stringstream input(line);
        if( !(input >> c >> row).fail() )
            break;
    }
    if(c=='q' && row == 1) return false;

    col=(int)c;
    col-=('a'-1);
    return true;
}

void Game::validateCoordinates(int x, int y) const
{
    if( !(x>=0 && x<=7 && y>=0 && y<=7) )
    {
        throw "Not a valid spot";
    }
    if(board.getSpot(x,y)->getPiece()==nullptr)
    {
        throw "No piece on spot";
    }
    return;
}

bool Game::nextMove()
{
    while( true )
    {
        board.display();
        int row, col;
        if( !getInput(row, col))
        {
            return false;
        }

        // Making coordinates
        int x=row-1;
        int y=col-1;

        try
        {
            validateCoordinates(x, y);
            board.getSpot(x,y)->getPiece()->move(board);
        }
        catch (const char* e)
        {
            std::cout<<e<<std::endl;
            waitForEnter();
            continue;
        }
        return true;
    }
}

void Game::start()
{
    while( true )
    {
        // Check if the game has ended
        if(board.isCheckmate(Color::BLACK))
        {
            std::cout<<"WHITE WON"<<std::endl;
            waitForEnter();
            break;
        }
        else if(board.isCheckmate(Color::WHITE))
        {
            std::cout<<"BLACK WON"<<std::endl;
            waitForEnter();
            break;
        }

        if(!nextMove())
        {
            break;
        }
    }
}

void Game::waitForEnter() const
{
    std::cout<<"Press Enter to continue...";
    std::cin.ignore();
}
