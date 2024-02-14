#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string.h>
#include <regex>

#include "connection.h"
#include "gameplay.h"

using namespace std;

class Core {
public:
    Core(int argc, char* argv[]);  // Constructor
    ~Core(); // Destructor

    void serverInit(int port); 

    void clientInit(string serverAddress); 



    struct arguments
    {
        string mode;
        string address;
        bool autoplace;
    };

    Core::arguments args;
    bool testMode = false;
    bool isHost = false;
    Connection connection;
    Gameplay gameplay;

private:
    bool isHostOrGuest();
    string getServerAddress();
    int getPortNumber();
    string getLocalhostAddress();
    void printUsage();
    arguments checkArguments(int argc, char* argv[]);


};

#endif