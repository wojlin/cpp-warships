#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <iostream>
#include <regex>
#include <vector>
#include <locale>
#include <string>
#include <string.h>

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

    bool playerReady = false;
    bool enemyReady = false;
    bool gameEnded = false;

    ships playerShips;
    ships shipsToPlace;
    std::vector<std::vector<int>> playerBoard = vector<vector<int>> (10, vector<int>(10, 0));
    std::vector<std::vector<int>> enemyBoard = vector<vector<int>> (10, vector<int>(10, 0));


    void drawBoard();

    void drawPlacingBoard();

    void managePlacing();

    void autoplaceShips();

    bool isValidPlaceForBomb(int x, int y);

    string getCellForBombing();

    string getBoard();

    void decodeBoard(string message);

    vector<int> placeToCoords(string place);

    
    
private:
    void placeNewShip();
    bool isValidPlaceForShip(place desiredPlace);

    string shipChar = "■";
    string shipHitChar = "x";
    string missChar = "▨";
    

};

#endif