#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <iostream>
#include <string.h>
#include <regex>
#include <vector>

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

    struct place
    {
        int shipSize;
        int posX;
        int posY;
        int rotate;
    };

    ships playerShips;
    ships shipsToPlace;
    std::vector<std::vector<int>> playerBoard = vector<vector<int>> (10, vector<int>(10, 0));
    std::vector<std::vector<int>> enemyBoard = vector<vector<int>> (10, vector<int>(10, 0));

    void drawBoard();

    void drawPlacingBoard();

    void managePlacing();

    place getPlace();

    
    
private:
    bool isValidPlace(place desiredPlace);

};

#endif