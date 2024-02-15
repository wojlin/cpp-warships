#include "gameplay.h"
#include <locale>
#include <string>
#include <string.h>

Gameplay::Gameplay()
{

}

Gameplay::~Gameplay()
{

}

void Gameplay::drawBoard()
{

}

Gameplay::place Gameplay::getPlace()
{
    bool goodPlace = false;
    place newPlace;

    while(!goodPlace)
    {
        bool correct = false;
        string shipType;
        string position;
        string rotation;

        int shipSize;
        int xPos;
        int yPos;
        int shipRotation;

        cout << endl;

        while(!correct)
        {
            
            cout << "choose ship to place:";
            if(shipsToPlace.size1 > 0)
            {
                cout << " <1>"; 
            }
            if(shipsToPlace.size2 > 0)
            {
                cout << " <2>"; 
            }
            if(shipsToPlace.size3 > 0)
            {
                cout << " <3>"; 
            }
            if(shipsToPlace.size4 > 0)
            {
                cout << " <4>"; 
            }
            cout << endl;
            cin >> shipType;

            try
            {
                int number = stoi(shipType);
                shipSize = number;
                if( number < 1 || number > 4)
                {
                    cerr << "you must choose a number between 1 and 4!" << endl;
                    continue;
                }

                if(number == 1 && shipsToPlace.size1 == 0)
                {
                    cerr << "ships of size one are already used!" << endl;
                    continue;
                }
                if(number == 2 && shipsToPlace.size2 == 0)
                {
                    cerr << "ships of size two are already used!" << endl;
                    continue;
                }
                if(number == 3 && shipsToPlace.size3 == 0)
                {
                    cerr << "ships of size three are already used!" << endl;
                    continue;
                }
                if(number == 4 && shipsToPlace.size4 == 0)
                {
                    cerr << "ships of size four are already used!" << endl;
                    continue;
                }


                if(number == 1 && shipsToPlace.size1 > 0)
                {
                    correct = true;
                    continue;
                }
                if(number == 2 && shipsToPlace.size2 > 0)
                {
                    correct = true;
                    continue;
                }
                if(number == 3 && shipsToPlace.size3 > 0)
                {
                    correct = true;
                    continue;
                }
                if(number == 4 && shipsToPlace.size4 > 0)
                {
                    correct = true;
                    continue;
                }


            }
            catch (...) 
            {
                cerr << "you must choose a number between 1 and 4!" << endl;
                continue;
            }
        }

    
        correct = false;
        while(!correct)
        {
            cout << "pick a spot to place ship of size " << shipType << ". example: <A4>,<G7> etc" << endl;
            cin >> position;

            if(position.size() != 2 && position.size() != 3)
            {
                cerr << "incorrect input!" << endl;
                cerr << "positon format needs to be <letter><number> from A to J and 1 to 10!" << endl;
                continue;
            }



            std::regex pattern("^[A-J]([1-9]|10)$");
            bool check = std::regex_match(position, pattern);
            
            if(!check)
            {
                cerr << "positon format needs to be <letter><number> from A to J and 1 to 10!" << endl;
                continue;
            }


            xPos = static_cast<int>(position.at(0) - 'A') + 1;

            if(position.size() == 2)
            {
                yPos = position.at(1) - '0';
            }
            else
            {
                yPos = 10;
            }

            correct = true;
        }


        correct = false;
        while(!correct)
        {
            cout << "do you want to place ship horizontal or vertical: h/v" << endl;
            cin >> rotation;
            if(rotation.size() != 1 || (rotation != "h" && rotation != "v"))
            {
                cerr << "you can only choose (h)orizontal or (v)ertical!" << endl;
                continue;
            }

            if(rotation == "v")
            {
                shipRotation = 1;
                correct = true;
            }else
            {
                shipRotation = 0;
                correct = true;
            }

        }

        
        newPlace.shipSize = shipSize;
        newPlace.posX = xPos - 1;
        newPlace.posY = yPos - 1;
        newPlace.rotate = shipRotation;

        if(isValidPlace(newPlace))
        {
            goodPlace = true;
        }
        else
        {
            cerr << "invalid position!" << endl;
            continue;
        }

        for(int i = 0; i < newPlace.shipSize; i++)
        {
            int partPosX = newPlace.posX + (i * (1 - newPlace.rotate));
            int partPosY = newPlace.posY + (i * newPlace.rotate);

            playerBoard[partPosY][partPosX] = 1;

        }

        if(newPlace.shipSize == 1)
        {
            shipsToPlace.size1 -= 1;
        }
        if(newPlace.shipSize == 2)
        {
            shipsToPlace.size2 -= 1;
        }
        if(newPlace.shipSize == 3)
        {
            shipsToPlace.size3 -= 1;
        }
        if(newPlace.shipSize == 4)
        {
            shipsToPlace.size4 -= 1;
        }

    }

    return newPlace;
}

bool Gameplay::isValidPlace(Gameplay::place desiredPlace)
{
    // check for every ship part
    for(int i = 0; i < desiredPlace.shipSize; i++)
    {
        int partPosX = desiredPlace.posX + (i * (1 - desiredPlace.rotate));
        int partPosY = desiredPlace.posY + (i * desiredPlace.rotate);

        for(int y = -1; y <= 1; y++)
        {
            for(int x = 0; x <= 1; x++)
            {
                int checkedPosX = partPosX  + x;
                int checkedPosY = partPosY + y;

                if( checkedPosX < 0 || checkedPosY < 0)
                {
                    continue;
                }

                if( checkedPosX > 9 || checkedPosY > 9)
                {
                    continue;
                }

                if(playerBoard[checkedPosY][checkedPosX] == 1)
                {
                    return false;
                }

            }
        }
        
    }

    return true;
}

void Gameplay::managePlacing()
{
    bool conditions = false;
    while(!conditions)
    {
        place newPlace = getPlace();

        

        cout << "ship size: " << newPlace.shipSize << endl;
        cout << "ship pos: " << newPlace.posX << " " << newPlace.posY << endl;
        cout << "ship rotated:" << newPlace.rotate << endl;

        drawPlacingBoard();
    }

    
    
    
}

void Gameplay::drawPlacingBoard()
{
    std::locale::global(std::locale("")); // Set the global locale to the user's default
    std::wcout.imbue(std::locale());      // Set the locale for std::wcout

    char endLetter = 'J';

    cout << "      ";
    for (char currentLetter = 'A'; currentLetter <= endLetter; ++currentLetter) 
    {
        cout << currentLetter << "   ";
    }

    cout << endl;

    
    cout << "    ╔";

    for (int z = 0; z < 9; ++z) 
    {
        cout << "═══╦";
    }
    cout << "═══╗";
    cout << endl;

    for (int i = 1; i < 11; ++i) {
        
  
        

        cout << " "<< i << " ";
        if(i < 10)
        {
            cout << " ";
        }
        

        for (int z = 0; z < 11; ++z) 
        {
            int yPos = i - 1;
            int xPos = z;
            string content = "   ";
            if(playerBoard[yPos][xPos] == 1)
            {
                content = " x ";
            }
            cout << "║" << content;
        }

        cout << endl;

        if(i < 10)
        {
            cout << "    ╠";
            for (int x = 0; x < 9; ++x) 
            {
            cout << "═══╬";
            }
            cout << "═══╣";

            cout << endl;
        }
        else
        {
            cout << "    ╚";
            for (int x = 0; x < 9; ++x) 
            {
            cout << "═══╩";
            }
            cout << "═══╝";

            cout << endl;
        }

        

    }

    cout << "\033[23A";
    cout << "\033[50C";

    cout << "\033[3B";

    cout << "player │ status";
    cout << "\033[1B";
    cout << "\033[16D";
    cout << "────────┼────────";
    cout << "\033[1B";
    cout << "\033[15D";
    cout << "you   │ ";
    std::cout << "\033[31m" << "not ready" << "\033[0m";
    cout << "\033[1B";
    cout << "\033[18D";
    cout << "enemy  │ ";
    std::cout << "\033[31m" << "not ready" << "\033[0m";
    cout << "\033[5B";
    cout << "\033[18D";

    cout << " ships │ amount";
    cout << "\033[1B";
    cout << "\033[15D";
    cout << "───────┼───────";
    cout << "\033[1B";
    cout << "\033[13D";

    cout << "■■■■ " << "│ "<< shipsToPlace.size4 <<"x";
    cout << "\033[1B";
    cout << "\033[9D";
    cout << "     │    ";
    cout << "\033[1B";
    cout << "\033[9D";
    cout << "■■■ " <<  "│ "<< shipsToPlace.size3 <<"x";
    cout << "\033[1B";
    cout << "\033[9D";
    cout << "     │     ";
    cout << "\033[1B";
    cout << "\033[9D";
    cout << "■■ " <<  "│ "<< shipsToPlace.size2 <<"x";
    cout << "\033[1B";
    cout << "\033[9D";
    cout << "     │      ";
    cout << "\033[1B";
    cout << "\033[9D";
    cout << "■ " <<  "│ "<< shipsToPlace.size1 <<"x";

    cout << "\033[10B";
    cout << "\033[57D";

}