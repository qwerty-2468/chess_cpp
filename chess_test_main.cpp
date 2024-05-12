#include "gtest_lite.h"
#include <iostream>
#include "piece.hpp"
#include "spot.hpp"
#include "board.hpp"
#include "pieces.hpp"
#include "game.hpp"

#define TESTING

#ifdef TESTING

int main()
{
    // Testing if Rook's path obstructed by Pawn
    TEST(Piece, isPathObstructed)
    {
        Board b;
        EXPECT_EQ(true,b.getSpot(0,0)->getPiece()->isPathObstructed(b, b.getSpot(0,0), b.getSpot(2,0)));
    }
    END

    // Testing Rook's path without the Pawn
    TEST(Piece, isPathObstructed)
    {
        Board b;
        b.capturePiece(1,0);
        EXPECT_EQ(false,b.getSpot(0,0)->getPiece()->isPathObstructed(b, b.getSpot(0,0), b.getSpot(2,0)));
    }
    END

    // Testing if Bishop's path obstructed by Pawn
    TEST(Piece, isPathObstructed)
    {
        Board b;
        EXPECT_EQ(true,b.getSpot(0,2)->getPiece()->isPathObstructed(b, b.getSpot(0,2), b.getSpot(2,4)));
    }
    END

    // Testing Bishop's path without the Pawn
    TEST(Piece, isPathObstructed)
    {
        Board b;
        b.capturePiece(1,3);
        EXPECT_EQ(false,b.getSpot(0,2)->getPiece()->isPathObstructed(b, b.getSpot(0,2), b.getSpot(2,4)));
    }
    END

    // Testing if Queen's path obstructed by Knight
    TEST(Piece, isPathObstructed)
    {
        Board b;
        b.movePiece(b.getSpot(7,3), b.getSpot(5,0));
        b.movePiece(b.getSpot(7,1), b.getSpot(5,2));
        EXPECT_EQ(true,b.getSpot(5,0)->getPiece()->isPathObstructed(b, b.getSpot(5,0), b.getSpot(5,4)));
    }
    END

    // Testing if King is safe at starting position
    TEST(Piece, isKingSafe)
    {
        Board b;
        b.capturePiece(1,4);
        EXPECT_EQ(true,b.isKingSafe(Color::WHITE));
    }
    END

    // Testing if King is safe in check situation
    TEST(Piece, isKingSafe)
    {
        Board b;
        b.capturePiece(1,4);
        b.movePiece(b.getSpot(7,0), b.getSpot(5,4));
        EXPECT_EQ(false,b.isKingSafe(Color::WHITE));
    }
    END

    // Testing if King is safe in checkmate situation
    TEST(Piece, isKingSafe)
    {
        Board b;
        b.capturePiece(1,4);
        b.movePiece(b.getSpot(0,4), b.getSpot(3,7));
        b.movePiece(b.getSpot(7,3), b.getSpot(3,6));
        b.movePiece(b.getSpot(7,7), b.getSpot(5,6));
        EXPECT_EQ(false,b.isKingSafe(Color::WHITE));
    }
    END

    // Testing if King is safe in stalemate situation
    TEST(Piece, isKingSafe)
    {
        Board b;
        b.clear();
        b.movePiece(b.getSpot(0,4), b.getSpot(0,7));
        b.getSpot(1,0)->setPiece(new Rook(Color::BLACK));
        b.getSpot(7,6)->setPiece(new Rook(Color::BLACK));
        EXPECT_EQ(true,b.isKingSafe(Color::WHITE));
    }
    END

    // Testing if King is safe facing a Pawn
    TEST(Piece, isKingSafe)
    {
        Board b;
        b.movePiece(b.getSpot(1,4), b.getSpot(4,4));
        b.movePiece(b.getSpot(7,4), b.getSpot(5,4));
        EXPECT_EQ(true,b.isKingSafe(Color::BLACK));
    }
    END

    // Testing false check
    TEST(Piece, isMoveResolvingCheck)
    {
        Board b;
        EXPECT_EQ(true,b.getSpot(1,0)->getPiece()->isMoveResolvingCheck(b, b.getSpot(1,0), b.getSpot(2,0)));
    }
    END

    // Testing not valid move after check
    TEST(Piece, isMoveResolvingCheck)
    {
        Board b;
        b.capturePiece(1,4);
        b.movePiece(b.getSpot(7,0), b.getSpot(5,4));
        EXPECT_EQ(false,b.getSpot(0,4)->getPiece()->isMoveResolvingCheck(b, b.getSpot(0,4), b.getSpot(1,4)));
    }
    END

    // Testing a valid move after check
    TEST(Piece, isMoveResolvingCheck)
    {
        Board b;
        b.capturePiece(1,4);
        b.movePiece(b.getSpot(7,0), b.getSpot(5,4));
        EXPECT_EQ(true,b.getSpot(0,5)->getPiece()->isMoveResolvingCheck(b, b.getSpot(0,5), b.getSpot(1,4)));
    }
    END

    // Testing king captures
    TEST(Piece, isMoveResolvingCheck)
    {
        Board b;
        b.clear();
        b.movePiece(b.getSpot(7,4), b.getSpot(7,6));
        b.getSpot(6,5)->setPiece(new Pawn(Color::BLACK));
        b.getSpot(6,6)->setPiece(new Pawn(Color::BLACK));
        b.getSpot(7,5)->setPiece(new Rook(Color::BLACK));
        b.getSpot(7,7)->setPiece(new Rook(Color::WHITE));
        EXPECT_EQ(true,b.getSpot(7,6)->getPiece()->isMoveResolvingCheck(b, b.getSpot(7,6), b.getSpot(7,7)));
    }
    END

    // Testing king captures rook rook protected by knight
    TEST(Piece, isMoveResolvingCheck)
    {
        Board b;
        b.clear();
        b.movePiece(b.getSpot(7,4), b.getSpot(7,6));
        b.getSpot(6,5)->setPiece(new Pawn(Color::BLACK));
        b.getSpot(6,6)->setPiece(new Pawn(Color::BLACK));
        b.getSpot(7,5)->setPiece(new Rook(Color::BLACK));
        b.getSpot(5,6)->setPiece(new Knight(Color::WHITE));
        b.getSpot(7,7)->setPiece(new Rook(Color::WHITE));
        EXPECT_EQ(false,b.getSpot(7,6)->getPiece()->isMoveResolvingCheck(b, b.getSpot(7,6), b.getSpot(7,7)));
    }
    END

    // Testing checkmate
    TEST(Piece, isCheckmate)
    {
        Board b;
        b.movePiece(b.getSpot(0,4), b.getSpot(3,7));
        b.movePiece(b.getSpot(7,3), b.getSpot(3,6));
        b.movePiece(b.getSpot(7,7), b.getSpot(5,6));
        EXPECT_EQ(true,b.isCheckmate(Color::WHITE));
    }
    END

    // Testing checkmate
    TEST(Piece, isCheckmate)
    {
        Board b;
        b.clear();
        b.movePiece(b.getSpot(7,4), b.getSpot(7,6));
        b.getSpot(6,5)->setPiece(new Pawn(Color::BLACK));
        b.getSpot(6,6)->setPiece(new Pawn(Color::BLACK));
        b.getSpot(7,5)->setPiece(new Rook(Color::BLACK));
        b.getSpot(5,6)->setPiece(new Knight(Color::WHITE));
        b.getSpot(7,7)->setPiece(new Rook(Color::WHITE));
        EXPECT_EQ(true,b.isCheckmate(Color::BLACK));
    }
    END

    // Testing not checkmate (king can capture bishop)
    TEST(Piece, isCheckmate)
    {
        Board b;
        b.clear();
        b.movePiece(b.getSpot(7,4), b.getSpot(7,6));
        b.getSpot(6,5)->setPiece(new Pawn(Color::BLACK));
        b.getSpot(6,6)->setPiece(new Pawn(Color::BLACK));
        b.getSpot(7,5)->setPiece(new Rook(Color::BLACK));
        b.getSpot(7,7)->setPiece(new Rook(Color::WHITE));
        EXPECT_EQ(false,b.isCheckmate(Color::WHITE));
    }
    END

    // Testing not checkmate
    TEST(Piece, isCheckmate) {
        Board b;
        EXPECT_EQ(false,b.isCheckmate(Color::BLACK));
    } END

    // Testing stalemate
    TEST(Piece, isCheckmate)
    {
        Board b;
        b.clear();
        b.movePiece(b.getSpot(0,4), b.getSpot(0,7));
        b.getSpot(1,0)->setPiece(new Rook(Color::BLACK));
        b.getSpot(7,6)->setPiece(new Rook(Color::BLACK));
        EXPECT_EQ(true,b.isCheckmate(Color::WHITE));
    }
    END

    // Testing en passant
    TEST(Piece, commonValidation)
    {
        Board b;
        b.movePiece(b.getSpot(6,1), b.getSpot(3,1));
        b.movePiece(b.getSpot(1,2), b.getSpot(3,2));
        EXPECT_EQ(true,b.getSpot(3,1)->getPiece()->commonValidation(b, b.getSpot(3,1), b.getSpot(2,2)));
    }
    END

    // Testing en passant with wrong sequence
    TEST(Piece, commonValidation)
    {
        Board b;
        b.movePiece(b.getSpot(1,2), b.getSpot(3,2));
        b.movePiece(b.getSpot(6,1), b.getSpot(3,1));
        EXPECT_EQ(false,b.getSpot(3,1)->getPiece()->commonValidation(b, b.getSpot(3,1), b.getSpot(2,2)));
    }
    END

    // Testing en passant when it is not the next move
    TEST(Piece, commonValidation)
    {
        Board b;
        b.movePiece(b.getSpot(6,1), b.getSpot(3,1));
        b.movePiece(b.getSpot(1,2), b.getSpot(3,2));
        b.movePiece(b.getSpot(1,7), b.getSpot(2,7));
        b.movePiece(b.getSpot(6,7), b.getSpot(5,7));
        EXPECT_EQ(false,b.getSpot(3,1)->getPiece()->commonValidation(b, b.getSpot(3,1), b.getSpot(2,2)));
    }
    END

    // Testing pawn promotion
    TEST(Piece, movePiece)
    {
        Board b;
        b.clear();
        b.getSpot(1,0)->setPiece(new Pawn(Color::BLACK));
        b.getSpot(6,3)->setPiece(new Queen(Color::BLACK));
        b.getSpot(5,2)->setPiece(new Pawn(Color::WHITE));
        b.movePiece(b.getSpot(5,2), b.getSpot(6,3));
        Piece* pawn = b.getSpot(1,0)->getPiece();
        b.movePiece(b.getSpot(1,0), b.getSpot(0,0));
        EXPECT_EQ(false,b.getSpot(0,0)->getPiece() == pawn);
    }
    END

    // Testing pawn promotion with no captured pieces
    TEST(Piece, movePiece)
    {
        Board b;
        b.clear();
        b.getSpot(1,0)->setPiece(new Pawn(Color::BLACK));
        Piece* pawn = b.getSpot(1,0)->getPiece();
        b.movePiece(b.getSpot(1,0), b.getSpot(0,0));
        EXPECT_EQ(true,b.getSpot(0,0)->getPiece() == pawn);
    }
    END

    // Testing getPossibleMoves function for pawn
    TEST(Piece, getPossibleMoves)
    {
        Board b;
        Spot* validMoves[2] =
        {
            b.getSpot(2,0),
            b.getSpot(3,0)
        };
        Spot** possibleMoves = b.getSpot(1,0)->getPiece()->getPossibleMoves(b);
        for (int k = 0; possibleMoves[k] != nullptr; k++)
        {
#ifdef DEBUG
            std::cout<<possibleMoves[k]->getRow()<<" "<<possibleMoves[k]->getCol()<<std::endl;
#endif // DEBUG
            bool valid = false;
            for(int i = 0; i < 2; i++)
            {
                if(validMoves[i] == possibleMoves[k])
                    valid = true;
            }
            EXPECT_EQ(true,valid);
        }
        delete[] possibleMoves;
    }
    END

    // Testing getPossibleMoves function for pawn
    TEST(Piece, getPossibleMoves)
    {
        Board b;
        b.movePiece(b.getSpot(1,1), b.getSpot(5,1));
        Spot* validMoves[2] =
        {
            b.getSpot(6,0),
            b.getSpot(6,2)
        };
        Spot** possibleMoves = b.getSpot(5,1)->getPiece()->getPossibleMoves(b);
        for (int k = 0; possibleMoves[k] != nullptr; k++)
        {
#ifdef DEBUG
            std::cout<<possibleMoves[k]->getRow()<<" "<<possibleMoves[k]->getCol()<<std::endl;
#endif // DEBUG
            bool valid = false;
            for(int i = 0; i < 2; i++)
            {
                if(validMoves[i] == possibleMoves[k])
                    valid = true;
            }
            EXPECT_EQ(true,valid);
        }
        delete[] possibleMoves;
    }
    END

    // Testing getPossibleMoves function for king
    TEST(Piece, getPossibleMoves)
    {
        Board b;
        b.capturePiece(1,4);
        b.movePiece(b.getSpot(0,4), b.getSpot(1,4));
        Spot* validMoves[4] =
        {
            b.getSpot(0,4),
            b.getSpot(2,4),
            b.getSpot(2,3),
            b.getSpot(2,5)
        };
        Spot** possibleMoves = b.getSpot(1,4)->getPiece()->getPossibleMoves(b);
        for (int k = 0; possibleMoves[k] != nullptr; k++)
        {
#ifdef DEBUG
            std::cout<<possibleMoves[k]->getRow()<<" "<<possibleMoves[k]->getCol()<<std::endl;
#endif // DEBUG
            bool valid = false;
            for(int i = 0; i < 4; i++)
            {
                if(validMoves[i] == possibleMoves[k])
                    valid = true;
            }
            EXPECT_EQ(true,valid);
        }
        delete[] possibleMoves;
    }
    END

    // Testing getPossibleMoves function for king (stalemate)
    TEST(Piece, getPossibleMoves)
    {
        Board b;
        b.clear();
        b.movePiece(b.getSpot(0,4), b.getSpot(0,7));
        b.getSpot(1,0)->setPiece(new Rook(Color::BLACK));
        b.getSpot(7,6)->setPiece(new Rook(Color::BLACK));
        Spot** possibleMoves = b.getSpot(0,7)->getPiece()->getPossibleMoves(b);
        EXPECT_EQ(true,possibleMoves[0] == nullptr);
        delete[] possibleMoves;
    }
    END

    // Testing getPossibleMoves function for queen
    TEST(Piece, getPossibleMoves)
    {
        Board b;
        b.movePiece(b.getSpot(1,2), b.getSpot(2,2));
        Spot* validMoves[3] =
        {
            b.getSpot(1,2),
            b.getSpot(2,1),
            b.getSpot(3,0)
        };
        Spot** possibleMoves = b.getSpot(0,3)->getPiece()->getPossibleMoves(b);
        for (int k = 0; possibleMoves[k] != nullptr; k++)
        {
#ifdef DEBUG
            std::cout<<possibleMoves[k]->getRow()<<" "<<possibleMoves[k]->getCol()<<std::endl;
#endif // DEBUG
            bool valid = false;
            for(int i = 0; i < 3; i++)
            {
                if(validMoves[i] == possibleMoves[k])
                    valid = true;
            }
            EXPECT_EQ(true,valid);
        }
        delete[] possibleMoves;
    }
    END

    // Testing getPossibleMoves function for queen
    TEST(Piece, getPossibleMoves)
    {
        Board b;
        b.capturePiece(1,3);
        b.movePiece(b.getSpot(0,3), b.getSpot(1,3));
        b.movePiece(b.getSpot(6,2), b.getSpot(2,2));
        b.movePiece(b.getSpot(6,3), b.getSpot(3,3));
        b.movePiece(b.getSpot(6,4), b.getSpot(2,4));
        Spot* validMoves[5] =
        {
            b.getSpot(0,3),
            b.getSpot(2,2),
            b.getSpot(2,3),
            b.getSpot(2,4),
            b.getSpot(3,3)
        };
        Spot** possibleMoves = b.getSpot(1,3)->getPiece()->getPossibleMoves(b);
        for (int k = 0; possibleMoves[k] != nullptr; k++)
        {
#ifdef DEBUG
            std::cout<<possibleMoves[k]->getRow()<<" "<<possibleMoves[k]->getCol()<<std::endl;
#endif // DEBUG
            bool valid = false;
            for(int i = 0; i < 5; i++)
            {
                if(validMoves[i] == possibleMoves[k])
                    valid = true;
            }
            EXPECT_EQ(true,valid);
        }
        delete[] possibleMoves;
    }
    END

    // Testing getPossibleMoves function for rook
    TEST(Piece, getPossibleMoves)
    {
        Board b;
        b.movePiece(b.getSpot(6,7), b.getSpot(5,7));
        b.movePiece(b.getSpot(7,6), b.getSpot(5,5));
        Spot* validMoves[2] =
        {
            b.getSpot(6,7),
            b.getSpot(7,6)
        };
        Spot** possibleMoves = b.getSpot(7,7)->getPiece()->getPossibleMoves(b);
        for (int k = 0; possibleMoves[k] != nullptr; k++)
        {
#ifdef DEBUG
            std::cout<<possibleMoves[k]->getRow()<<" "<<possibleMoves[k]->getCol()<<std::endl;
#endif // DEBUG
            bool valid = false;
            for(int i = 0; i < 2; i++)
            {
                if(validMoves[i] == possibleMoves[k])
                    valid = true;
            }
            EXPECT_EQ(true,valid);
        }
        delete[] possibleMoves;
    }
    END

    // Testing getPossibleMoves function for rook
    TEST(Piece, getPossibleMoves)
    {
        Board b;
        Spot** possibleMoves = b.getSpot(0,0)->getPiece()->getPossibleMoves(b);
        EXPECT_EQ(true,possibleMoves[0] == nullptr);
        delete[] possibleMoves;
    }
    END

    // Testing getPossibleMoves function for knight
    TEST(Piece, getPossibleMoves)
    {
        Board b;
        Spot* validMoves[2] =
        {
            b.getSpot(5,0),
            b.getSpot(5,2)
        };
        Spot** possibleMoves = b.getSpot(7,1)->getPiece()->getPossibleMoves(b);
        for (int k = 0; possibleMoves[k] != nullptr; k++)
        {
#ifdef DEBUG
            std::cout<<possibleMoves[k]->getRow()<<" "<<possibleMoves[k]->getCol()<<std::endl;
#endif // DEBUG
            bool valid = false;
            for(int i = 0; i < 2; i++)
            {
                if(validMoves[i] == possibleMoves[k])
                    valid = true;
            }
            EXPECT_EQ(true,valid);
        }
        delete[] possibleMoves;
    }
    END

    // Testing getPossibleMoves function for knight
    TEST(Piece, getPossibleMoves)
    {
        Board b;
        b.movePiece(b.getSpot(0,6), b.getSpot(4,6));
        b.movePiece(b.getSpot(1,4), b.getSpot(3,4));
        Spot* validMoves[5] =
        {
            b.getSpot(2,5),
            b.getSpot(2,7),
            b.getSpot(6,5),
            b.getSpot(6,7),
            b.getSpot(5,4)
        };
        Spot** possibleMoves = b.getSpot(4,6)->getPiece()->getPossibleMoves(b);
        for (int k = 0; possibleMoves[k] != nullptr; k++)
        {
#ifdef DEBUG
            std::cout<<possibleMoves[k]->getRow()<<" "<<possibleMoves[k]->getCol()<<std::endl;
#endif // DEBUG
            bool valid = false;
            for(int i = 0; i < 5; i++)
            {
                if(validMoves[i] == possibleMoves[k])
                    valid = true;
            }
            EXPECT_EQ(true,valid);
        }
        delete[] possibleMoves;
    }
    END

    // Testing getPossibleMoves function for bishop
    TEST(Piece, getPossibleMoves)
    {
        Board b;
        b.movePiece(b.getSpot(1,4), b.getSpot(5,4));
        b.movePiece(b.getSpot(6,3), b.getSpot(5,3));
        Spot* validMoves[2] =
        {
            b.getSpot(6,3),
            b.getSpot(5,4)
        };
        Spot** possibleMoves = b.getSpot(7,2)->getPiece()->getPossibleMoves(b);
        for (int k = 0; possibleMoves[k] != nullptr; k++)
        {
#ifdef DEBUG
            std::cout<<possibleMoves[k]->getRow()<<" "<<possibleMoves[k]->getCol()<<std::endl;
#endif // DEBUG
            bool valid = false;
            for(int i = 0; i < 2; i++)
            {
                if(validMoves[i] == possibleMoves[k])
                    valid = true;
            }
            EXPECT_EQ(true,valid);
        }
        delete[] possibleMoves;
    }
    END

    // Testing getPossibleMoves function for bishop
    TEST(Piece, getPossibleMoves)
    {
        Board b;
        b.movePiece(b.getSpot(1,6), b.getSpot(3,6));
        b.movePiece(b.getSpot(0,5), b.getSpot(2,7));
        Spot* validMoves[2] =
        {
            b.getSpot(0,5),
            b.getSpot(1,6)
        };
        Spot** possibleMoves = b.getSpot(2,7)->getPiece()->getPossibleMoves(b);
        for (int k = 0; possibleMoves[k] != nullptr; k++)
        {
#ifdef DEBUG
            std::cout<<possibleMoves[k]->getRow()<<" "<<possibleMoves[k]->getCol()<<std::endl;
#endif // DEBUG
            bool valid = false;
            for(int i = 0; i < 2; i++)
            {
                if(validMoves[i] == possibleMoves[k])
                    valid = true;
            }
            EXPECT_EQ(true,valid);
        }
        delete[] possibleMoves;
    }
    END

    // Testing exception throwing with out of range coordinates
    TEST(Piece, validateCoordinates)
    {
        Game g;
        EXPECT_THROW(g.validateCoordinates(12,-81), const char*);
    }
    END

    // Testing exception throwing if there is no piece on spot
    TEST(Piece, validateCoordinates)
    {
        Game g;
        EXPECT_THROW(g.validateCoordinates(4,4), const char*);
    }
    END

    // Testing not throwing exception for valid coordinates
    TEST(Piece, validateCoordinates)
    {
        Game g;
        EXPECT_NO_THROW(g.validateCoordinates(0,0));
    }
    END

    return 0;
}


#endif // TESTING
