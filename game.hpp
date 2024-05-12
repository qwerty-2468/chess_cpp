#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

class Game{
    Board board;
public:
    Game() :board() {}
    Board& getBoard();
    bool getInput(int& row, int& col) const;
    void validateCoordinates(int x, int y) const;
    bool nextMove();
    void start();
    void waitForEnter() const;
};

#endif // GAME_HPP_INCLUDED
