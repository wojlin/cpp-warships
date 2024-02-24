#include <gtest/gtest.h>
#include <string.h>
#include <string>
#include <vector>

#include "../include/gameplay.h"
#include <iostream>

TEST(testGamePlay, testPlaceToCoords)
{
    Gameplay gameplay;

    char startChar = 'A';
    char endChar = 'J';
    int startInt = static_cast<int>(startChar);
    int endInt = static_cast<int>(endChar);

    int currentX = 0;
    int currentY = 0;
    vector<int> pos;

    for (int x = startInt; x <= endInt; x++) 
    {
        for (int y = 1; y < 11; y++) 
        {
            string place(1, static_cast<char>(x));
            place += to_string(y);
            pos = gameplay.placeToCoords(place);
            cout << "place:" << place << endl;
            cout << "pos: "<< pos[0] << " " << pos[1] << endl;    
            cout << "excpected: "<< currentX << " " << currentY << endl;  
            cout << endl;       
            EXPECT_EQ(pos[0], currentX);
            EXPECT_EQ(pos[1], currentY);
            currentY++;
            
        } 
        currentX++;
        currentY = 0;
    }
}

TEST(testGamePlay, checkGameEndConditions)
{
    bool condition;
    Gameplay gameplay;
    condition = gameplay.checkGameEndConditions();
    ASSERT_TRUE(condition);
    cout << "zero ships on all boards" << endl;
    cout << "end game:" << condition << endl << endl;

    gameplay.playerBoard[5][5] = 1;
    gameplay.enemyBoard[5][5] = 1;
    condition = gameplay.checkGameEndConditions();
    cout << "one ship on all boards" << endl;
    cout << "end game:" << condition << endl << endl;
    ASSERT_FALSE(condition);

    gameplay.playerBoard[5][5] = 0;
    gameplay.enemyBoard[5][5] = 1;
    condition = gameplay.checkGameEndConditions();
    cout << "one ship on enemy board" << endl;
    cout << "end game:" << condition << endl << endl;
    ASSERT_TRUE(condition);

    gameplay.playerBoard[5][5] = 1;
    gameplay.enemyBoard[5][5] = 0;
    condition = gameplay.checkGameEndConditions();
    cout << "one ship on player board" << endl;
    cout << "end game:" << condition << endl << endl;
    ASSERT_TRUE(condition);

}