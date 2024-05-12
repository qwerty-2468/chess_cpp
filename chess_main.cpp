#include <iostream>
#include "piece.hpp"
#include "spot.hpp"
#include "board.hpp"
#include "pieces.hpp"
#include "game.hpp"
#include "memtrace.h"

#define TESTING

#ifndef TESTING
int main(){

    Game g;
    g.start();
    return 0;
}
#endif // TESTING
