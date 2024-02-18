#include "gameplay.h"



Gameplay::Gameplay()
{

}

Gameplay::~Gameplay()
{

}

vector<int> Gameplay::placeToCoords(string place)
{
    if (place.back() == '\0') 
    {
        place.pop_back();
    } 

    int xPos = static_cast<int>(place.at(0) - 'A') + 1;
    int yPos;

    if(place.size() == 2)
    {
        yPos = place.at(1) - '0';
    }
    else
    {
        yPos = 10;
    }

    
    vector<int> pos;
    pos.push_back(xPos - 1);
    pos.push_back(yPos - 1);
    return pos;
}

void Gameplay::decodeBoard(string message)
{

    cerr << message << endl;

    if (message.find('|') == std::string::npos) 
    {
        cerr << "message does not contain '|' char!" << endl;
        exit(1);
    }

    if (message.find('.') == std::string::npos) 
    {
        cerr << "message does not contain '.' char!" << endl;
        exit(1);
    }

    size_t delimiterPos = message.find('|');
    if (delimiterPos != std::string::npos)
    {
        string sBoard = message.substr(delimiterPos + 1);
        std::istringstream ss(sBoard);
        std::string binaryDigit;
        std::vector<int> decodedVector;


        while (std::getline(ss, binaryDigit, '.')) 
        {
            cout << decodedVector.size();
            try 
            {
                cerr << binaryDigit << endl;
                int decodedValue = std::stoi(binaryDigit, nullptr, 2);
                decodedVector.push_back(decodedValue);
            }
            catch (const std::invalid_argument& e) 
            {

            }
        }

        if(decodedVector.size() != 100)
        {
            cerr << "decoded vector have invalid length of " << decodedVector.size() << endl;
            exit(1);
        }

        for( int y = 0; y < 10; y++)
        {
            for( int x = 0; x < 10; x++)
            {
                enemyBoard[y][x] = decodedVector[y*10+x];
            }
        }


    }
    else
    {
        cerr << "invalid board message!" << endl;
        exit(1);
    }
    
}   

string Gameplay::getBoard()
{
    string buffer = "";

    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 10; x++)
        {
            buffer += to_string(playerBoard[y][x]);
            buffer += ".";
        }
    }
    return buffer;
}

bool Gameplay::isValidPlaceForBomb(int x, int y)
{
    if(enemyBoard[y][x] == 2)
    {
        return false;
    }
    if(enemyBoard[y][x] == 3)
    {
        return false;
    }
    return true;
}

string Gameplay::getCellForBombing()
{
    string position;

    while(true)
    {
        cout << "pick a spot to bomb. example: <A4>,<G7> etc" << endl;
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


        int xPos = static_cast<int>(position.at(0) - 'A') + 1;
        int yPos;

        if(position.size() == 2)
        {
            yPos = position.at(1) - '0';
        }
        else
        {
            yPos = 10;
        }

        if(!isValidPlaceForBomb(xPos, yPos))
        {
            cerr << "invalid position!" << endl;
            continue;
        }

        break;
    }

    

    return position;
}

void Gameplay::drawBoard()
{
    std::cout << "\033c";
    char endLetter = 'J';

    for(int board = 0; board <= 1; board++)
    {

        if(board == 1)
        {
            std::cout << "\033[H";
            std::cout << "\033[50C";
        }
        

        cout << "      ";
        for (char currentLetter = 'A'; currentLetter <= endLetter; ++currentLetter) 
        {
            cout << currentLetter << "   ";
        }


        cout << "\033[1B";
        cout << "\033[46D";

        
        cout << "    ╔";

        for (int z = 0; z < 9; ++z) 
        {
            cout << "═══╦";
        }
        cout << "═══╗";
        

        if(board == 0)
        {
            cout << "\033[1B";
            cout << "\033[46D";
        }
        else
        {
            cout << "\033[1B";
            cout << "\033[45D";
        }
        

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



                if(board == 0)
                {

                    if(playerBoard[yPos][xPos] == 1)
                    {
                        content = " " + shipChar + " ";
                    }
                    if(playerBoard[yPos][xPos] == 2)
                    {
                        content = " " + shipHitChar + " ";
                    }
                    if(playerBoard[yPos][xPos] == 3)
                    {
                        content = " " + missChar + " ";
                    }

                }
                else
                {
                    if(enemyBoard[yPos][xPos] == 2)
                    {
                        content = " " + shipHitChar + " ";
                    }
                    if(enemyBoard[yPos][xPos] == 3)
                    {
                        content = " " + missChar + " ";
                    }
                }
                
                cout << "║" << content;
            }


            if(board == 0)
            {
                cout << "\033[1B";
                cout << "\033[50D";
            }
            else
            {
                cout << "\033[1B";
                cout << "\033[48D";
            }
            

            if(i < 10)
            {
                cout << "    ╠";
                for (int x = 0; x < 9; ++x) 
                {
                cout << "═══╬";
                }
                cout << "═══╣";

                cout << "\033[1B";
                cout << "\033[45D";
            }
            else
            {
                cout << "    ╚";
                for (int x = 0; x < 9; ++x) 
                {
                cout << "═══╩";
                }
                cout << "═══╝";

                cout << "\033[1B";
                cout << "\033[45D";
            }

            

        }

        

    }

    std::cout << "\r";


    cout << "                 " << "PLAYER BOARD";
    cout << "                                        " << "ENEMY BOARD" << endl;

    std::cout.flush();
}

void Gameplay::placeNewShip()
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
            std::getline(std::cin, shipType);


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

        if(isValidPlaceForShip(newPlace))
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
}

bool Gameplay::isValidPlaceForShip(Gameplay::place desiredPlace)
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
    drawPlacingBoard();

    while(true)
    {

        if( shipsToPlace.size1 == 0 && 
            shipsToPlace.size2 == 0 &&
            shipsToPlace.size3 == 0 &&
            shipsToPlace.size4 == 0)
        {
            break;
        }

        placeNewShip();
        drawPlacingBoard();     

    }

    playerReady = true;

    drawPlacingBoard(); 

    cout << "all ships are placed!" << endl;

    
}

void Gameplay::autoplaceShips()
{
    shipsToPlace.size1 = 0;
    shipsToPlace.size2 = 0;
    shipsToPlace.size3 = 0;
    shipsToPlace.size4 = 0;

    playerBoard[0][0] = 1;
    playerBoard[0][9] = 1;
    playerBoard[9][0] = 1;
    playerBoard[9][9] = 1;

    playerBoard[2][0] = 1;
    playerBoard[2][1] = 1;
    playerBoard[2][2] = 1;
    playerBoard[2][3] = 1;

    playerBoard[4][0] = 1;
    playerBoard[4][1] = 1;
    playerBoard[4][2] = 1;

    playerBoard[6][0] = 1;
    playerBoard[6][1] = 1;
    playerBoard[6][2] = 1;

    playerBoard[7][4] = 1;
    playerBoard[7][5] = 1;

    playerBoard[8][3] = 1;
    playerBoard[8][4] = 1;

    playerBoard[8][6] = 1;
    playerBoard[8][7] = 1;

    managePlacing();
}

void Gameplay::drawPlacingBoard()
{
    std::cout << "\033c";

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
                content = " " + shipChar + " ";
            }
            if(playerBoard[yPos][xPos] == 2)
            {
                content = " " + shipHitChar + " ";
            }
            if(playerBoard[yPos][xPos] == 3)
            {
                content = " " + missChar + " ";
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
    if(playerReady)
    {
        std::cout << "\033[32m" << "ready    " << "\033[0m";
    }
    else
    {
        std::cout << "\033[31m" << "not ready" << "\033[0m";
    } 
    cout << "\033[1B";
    cout << "\033[18D";
    cout << "enemy  │ ";
    if(enemyReady)
    {
        std::cout << "\033[32m" << "ready    " << "\033[0m";
    }
    else
    {
        std::cout << "\033[31m" << "not ready" << "\033[0m";
    } 
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

    cout << "\033[4B";
    cout << "\033[57D";

    std::cout.flush();

}