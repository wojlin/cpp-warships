
#include "main.h"

bool Core::isHostOrGuest()
{
    bool declaration = false;
    string userInput;

    while(!declaration)
    {
        cout << "do you want to host game or join game? " << endl;
        cout << "type: host/join" << endl;

        if(testMode)
        {
            userInput = args.mode;
        }
        else
        {
            getline(cin, userInput);
        }

        if(userInput == "host" || userInput == "join")
        {
            declaration = true;   
        }
        else
        {
            cout << "incorrect decision!" << endl;
        }

    }

    if(userInput == "host")
    {
        return true;
    }
    else
    {
        return false;
    }
}

string Core::getServerAddress()
{
    string userInput;
    bool declaration = false;

    while(!declaration)
    {
        cout << "type ip addr and port: <ip>:<port>" << endl;

        if(testMode)
        {
            userInput = args.address;
        }
        else
        {
            getline(cin, userInput);
        }
        

        size_t colonPos = userInput.find(':');

        if (colonPos != string::npos) 
        {
            string serverAddress = userInput.substr(0, colonPos);
            string port = userInput.substr(colonPos + 1);

            regex ip_pattern(
                // IPv6
                "^([0-9a-fA-F]{1,4}:){7,7}[0-9a-fA-F]{1,4}$|"
                "^([0-9a-fA-F]{1,4}:){1,7}:$|"
                "^([0-9a-fA-F]{1,4}:){1,6}:[0-9a-fA-F]{1,4}$|"
                "^([0-9a-fA-F]{1,4}:){1,5}(:[0-9a-fA-F]{1,4}){1,2}$|"
                "^([0-9a-fA-F]{1,4}:){1,4}(:[0-9a-fA-F]{1,4}){1,3}$|"
                "^([0-9a-fA-F]{1,4}:){1,3}(:[0-9a-fA-F]{1,4}){1,4}$|"
                "^([0-9a-fA-F]{1,4}:){1,2}(:[0-9a-fA-F]{1,4}){1,5}$|"
                "^([0-9a-fA-F]{1,4}:){1,1}(:[0-9a-fA-F]{1,4}){1,6}$|"
                "^([0-9a-fA-F]{1,4}:){1,6}:([0-9a-fA-F]{1,4}:){1,6}$|"
                
                // IPv4
                "^(25[0-5]|2[0-4][0-9]|[0-1]?[0-9]{1,2})(\\.(25[0-5]|2[0-4][0-9]|[0-1]?[0-9]{1,2})){3}$"
            );

            regex port_pattern("^(?:[1-9]\\d{0,4}|[1-5]\\d{4}|6[0-4]\\d{3}|65[0-4]\\d{2}|655[0-2]\\d|6553[0-5])$");

            bool correct_ip = regex_match(serverAddress, ip_pattern);
            bool correct_port = regex_match(port, port_pattern);

            if(correct_ip && correct_port)
            {
                declaration = true;
            }else
            {
                cout << "incorrect address!" << endl;
            }
        }
        
    }

    return userInput;
    
}

int Core::getPortNumber()
{
    string userInput;
    bool declaration = false;

    while(!declaration)
    {
        cout << "choose port number from 1024-65535" << endl;

        if(testMode)
        {
            userInput = args.address;
        }
        else
        {
            getline(cin, userInput);
        }
        
    
        try
        {
            int intValue = stoi(userInput);
            if( intValue < 1024)
            {
                cout << "port needs to be higher than a 1023!" << endl;
            }
            else if( intValue > 65535)
            {
                cout << "port needs to be lower than a 65535!" << endl;
            }else
            {
                declaration = true;
            }

        } 
        catch (const std::exception& e) 
        {
            cout << "port needs to be a number!" << endl;
        }
    }

    return stoi(userInput);
}

string Core::getLocalhostAddress()
{
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0) 
    {
        struct hostent* host = gethostbyname(hostname);

        if (host != nullptr) 
        {
            struct in_addr addr;
            memcpy(&addr, host->h_addr_list[0], sizeof(struct in_addr));
            return inet_ntoa(addr);
        } 

        std::cerr << "Failed to get host information." << std::endl;
        exit(1);
    } 

    std::cerr << "Failed to get local hostname." << std::endl;
    exit(1);
}



void Core::printUsage() {
    std::cerr << "Usage: ./program --mode <host/join> --address <string> --autoplace <bool>" << std::endl;
}



Core::arguments Core::checkArguments(int argc, char* argv[])
{

    arguments args;

    bool isModeSet = false;
    bool isAddressSet = false;
    bool isAutoplaceSet = false;


    for (int i = 1; i < argc; ++i) {  // Start from 1 to skip the program name (argv[0])
        std::string arg = argv[i];

        if (arg == "--mode") {
            if (i + 1 < argc) {
                args.mode = argv[i + 1];
                isModeSet = true;
                i++;  // Skip the next argument since it has been processed
            } else {
                std::cerr << "Error: --mode requires an argument." << std::endl;
                printUsage();
                exit(1);
            }
        } else if (arg == "--address") {
            if (i + 1 < argc) {
                args.address = argv[i + 1];
                isAddressSet = true;
                i++;  // Skip the next argument since it has been processed
            } else {
                std::cerr << "Error: --address requires an argument." << std::endl;
                printUsage();
                exit(1);
            }
        } else if (arg == "--autoplace") {
            if (i + 1 < argc) {
                args.autoplace = std::string(argv[i + 1]) == "true";
                isAutoplaceSet = true;
                i++;  // Skip the next argument since it has been processed
            } else {
                std::cerr << "Error: --autoplace requires an argument (true/false)." << std::endl;
                printUsage();
                exit(1);
            }
        } else {
            // Handle other arguments or show an error for unrecognized ones
            std::cerr << "Error: Unrecognized argument: " << arg << std::endl;
            printUsage();
            exit(1);
        }
    }

    if(!isModeSet || !isAddressSet || !isAutoplaceSet)
    {
        std::cerr << "Error: all arguments needs to be set!"<< std::endl;
        printUsage();
        exit(1);
    }

    return args;

}

void Core::managePlayerTurn()
{
    bool moveMade = false;

    while(!moveMade)
    {
        cout << "waiting for your move..." << endl;
        std::cout.flush();
        string place = gameplay.getCellForBombing();
        string message = "bomb|" + place;
        connection.sendMessage(message);
        
        vector<int> pos = gameplay.placeToCoords(place);
        if(gameplay.enemyBoard[pos[1]][pos[0]] == 0)
        {
            moveMade = true;
            gameplay.enemyBoard[pos[1]][pos[0]] = 3;
        }
        if(gameplay.enemyBoard[pos[1]][pos[0]] == 1)
        {
            gameplay.enemyBoard[pos[1]][pos[0]] = 2;
        }

        gameplay.drawBoard();

    }
}

void Core::manageEnemyTurn()
{
    bool finished = false;
    while(!finished)
    {
        cout << "waiting for enemy move..." << endl;
        string prefixToCheck = "bomb|";
        string receivedMessage = connection.awaitMessage();

        if (receivedMessage.substr(0, prefixToCheck.length()) == prefixToCheck) 
        {
            vector<int> pos = gameplay.placeToCoords(receivedMessage.substr(5));
            if(gameplay.playerBoard[pos[1]][pos[0]] == 1)
            {
                gameplay.playerBoard[pos[1]][pos[0]] = 2;
                gameplay.drawBoard();
                cout << "enemy hit your ship at " << receivedMessage.substr(5) << endl;
                          
            }
            else
            {
                gameplay.playerBoard[pos[1]][pos[0]] = 3;
                finished = true;
                gameplay.drawBoard();
            }
            
        }     
    } 
}

void Core::managePreGamePhase()
{
    while(true)
    {

        string message = "ships_placed|";
        message += gameplay.getBoard();
        connection.sendMessage(message);
        string shipsPrefix = "ships_placed|";
        string startPrefix = "start_game|";
        string response = connection.awaitMessage();

        if(response.substr(0, shipsPrefix.length()) == shipsPrefix ||
        response.substr(0, startPrefix.length()) == startPrefix)
        {   
            gameplay.decodeBoard(response);
            string message = "start_game|";
            message += gameplay.getBoard();
            connection.sendMessage(message);
            gameplay.enemyReady = true;
            gameplay.drawPlacingBoard();
            break;
        }
    }
}

Core::Core(int argc, char* argv[])
{

    testMode = argc > 1;

    if(testMode)
    {
        args = checkArguments(argc, argv);
    }

    isHost = isHostOrGuest();

    

    if(isHost)
    {
        cout << "you are host" << endl;
        int port;
        port = getPortNumber();
         
        string address = getLocalhostAddress();
        std::cout << "game address: " << address << ":" << port << std::endl;
        connection.serverInit(port);

    }
    else
    {
        cout << "you are guest" << endl;

        string serverAddress = getServerAddress();
        connection.clientInit(serverAddress);   
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));


    if(args.autoplace)
    {
        gameplay.autoplaceShips();
    }       
    else
    {
        gameplay.managePlacing();
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    managePreGamePhase();
    
    std::this_thread::sleep_for(std::chrono::seconds(1));

    gameplay.drawBoard();

    if(connection.isHost)
    {
        managePlayerTurn();
    }

    while(!gameplay.gameEnded)
    {
        manageEnemyTurn();
        managePlayerTurn();
    }
    
    cout << "end game!" << endl;
    
}

Core::~Core()
{
    connection.endConnection();
}

int main(int argc, char* argv[])
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    Core core(argc, argv);

    return 0;
}