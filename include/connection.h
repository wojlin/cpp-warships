#ifndef CONNECTION_H
#define CONNECTION_H

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <cstdlib>
#include <cstring>


using namespace std;



class Connection {
public:
    Connection();  // Constructor
    ~Connection(); // Destructor

    void serverInit(int port); 

    void clientInit(string serverAddress); 


    void endConnection();

    string awaitMessage();

    void sendMessage(string message);


    bool isHost;

private:
    
    int connectionSocket;
    

};

#endif
