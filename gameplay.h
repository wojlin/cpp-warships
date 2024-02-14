#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <iostream>
#include <string.h>
#include <regex>

using namespace std;

class Gameplay {
public:
    Gameplay();  // Constructor
    ~Gameplay(); // Destructor

    struct ships
    {
        int size4 = 1;
        int size3 = 2;
        int size2 = 3;
        int size1 = 4;
    };

    ships playerShips;
    ships shipsToPlace;


    void drawBoard();

    void drawPlacingBoard();

    void managePlacing();
    
private:

};

#endif