#include <iostream>
#include <string.h>
#include <regex>

//#include "server.h"
//#include "client.h"

#include "connection.h"

using namespace std;

bool isHostOrGuest()
{
    bool declaration = false;
    string userInput;

    while(!declaration)
    {
        cout << "do you want to host game or join game? " << endl;
        cout << "type: host/join" << endl;

        
        getline(cin, userInput);

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

string getServerAddress()
{
    string userInput;
    bool declaration = false;

    while(!declaration)
    {
        cout << "type ip addr and port: <ip>:<port>" << endl;
        getline(cin, userInput);

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

int getPortNumber()
{
    string userInput;
    bool declaration = false;

    while(!declaration)
    {
        cout << "choose port number from 1024-65535" << endl;
        getline(cin, userInput);
    
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

string getLocalhostAddress()
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

int main()
{
    bool isHost = isHostOrGuest();
    Connection connection;

    if(isHost)
    {
        cout << "you are host" << endl;
        int port = getPortNumber();
        string address = getLocalhostAddress();
        std::cout << "game address: " << address << ":" << port << std::endl;
        connection.serverInit(port);
    }else
    {
        cout << "you are guest" << endl;
        
        string serverAddress = getServerAddress();
        connection.clientInit(serverAddress);
    }

    

}