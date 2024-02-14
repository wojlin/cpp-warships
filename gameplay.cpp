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

void Gameplay::managePlacing()
{
    bool correct = false;
    string shipType;
    string position;
    string rotation;

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

        //int xPos = static_cast<int>(firstChar - 'A') + 1;
        //int yPos = secondChar - '0';

        //cout << xPos << " " << yPos << endl;

        correct = true;




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
            cout << "║   ";
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

    cout << "■■■■ " << "│ 1x";
    cout << "\033[1B";
    cout << "\033[9D";
    cout << "     │   ";
    cout << "\033[1B";
    cout << "\033[9D";
    cout << "■■■ " << " │ 2x";
    cout << "\033[1B";
    cout << "\033[9D";
    cout << "     │   ";
    cout << "\033[1B";
    cout << "\033[9D";
    cout << "■■ " << "  │ 3x";
    cout << "\033[1B";
    cout << "\033[9D";
    cout << "     │   ";
    cout << "\033[1B";
    cout << "\033[9D";
    cout << "■ " << "   │ 4x";

    cout << "\033[10B";
    cout << "\033[57D";

}