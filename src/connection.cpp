#include "../include/connection.h"

Connection::Connection() {
    // Constructor implementation
}

Connection::~Connection() {
    // Destructor implementation
}

void Connection::endConnection()
{
    close(connectionSocket); 
}


string Connection::awaitMessage()
{
    char buffer[1024];
    int bytesRead;
    bytesRead = read(connectionSocket, buffer, sizeof(buffer));
    string returnedMessage = string(buffer, bytesRead);
    return returnedMessage;
}

void Connection::sendMessage(string message)
{
    char buffer[1024];

    strcpy(buffer, message.c_str());
    write(connectionSocket, buffer, std::strlen(buffer) + 1);
}

void Connection::clientInit(string address)
{

    isHost = false;
    size_t colonPos = address.find(':');

    int client;
    int portNum = stoi(address.substr(colonPos + 1)); 
    char* ip = const_cast<char*>(address.substr(0, colonPos).data());


    

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error creating socket\n";
        exit(1);
    }

    //cout << "socket created!" << endl;

    // Set up server address structure
    sockaddr_in serverAddress;
    std::memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portNum); // Port number
    inet_pton(AF_INET, ip, &serverAddress.sin_addr); // IP address
    
    //cout << "connecting to " << ip << ":" << portNum << endl;
    // Connect to server
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Error connecting to server\n";
        close(clientSocket);
        exit(1);
    }
    connectionSocket = clientSocket;
    //std::cout << "Connected to server\n";

    // Exchange messages with server
    /*
    char buffer[1024];
    while (true) {
        // Send message to server
        std::cout << "Client: ";
        std::cin.getline(buffer, sizeof(buffer));
        write(clientSocket, buffer, std::strlen(buffer) + 1); // Include null terminator

        // Receive and print response from server
        int bytesRead = read(clientSocket, buffer, sizeof(buffer));
        if (bytesRead <= 0) {
            std::cerr << "Connection closed by server\n";
            break;
        }
        std::cout << "Server: " << std::string(buffer, bytesRead) << "\n";
    }

    // Close socket
    close(clientSocket);
    */
}


void Connection::serverInit(int port)
{
    isHost = true;
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating socket\n";
        exit(1);
    }

    // Set up server address structure
    sockaddr_in serverAddress;
    std::memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port); // Port number
    serverAddress.sin_addr.s_addr = INADDR_ANY; // Accept connections on any interface

    //cout << "binding socket..." << endl;
    // Bind socket to address
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Error binding socket to address\n";
        close(serverSocket);
        exit(1);
    }

    

    //cout << "begin listening..." << endl;

    cout << "waiting for other player to join your game..." << endl << std::flush;


    if (listen(serverSocket, SOMAXCONN) == -1) {
        perror("Error listening on socket");
        exit(1);
    }
    

    //std::cout << "Server listening on port " << port << "...\n";

    sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
    
    if (clientSocket == -1) {
        std::cerr << "Error accepting connection\n";
        close(serverSocket);
        exit(1);
    }

    //std::cout << "Connection accepted from " << inet_ntoa(clientAddress.sin_addr) << ":" << ntohs(clientAddress.sin_port) << "\n";
    connectionSocket = clientSocket;
    
    // Handle communication
    /*
    char buffer[1024];
    int bytesRead;
    while (true) {
        // Read client message
        bytesRead = read(clientSocket, buffer, sizeof(buffer));
        if (bytesRead <= 0) {
            std::cerr << "Connection closed by client\n";
            break;
        }
        std::cout << "Client: " << std::string(buffer, bytesRead) << "\n";

        // Send response to client
        std::cout << "Server: ";
        std::cin.getline(buffer, sizeof(buffer));
        write(clientSocket, buffer, std::strlen(buffer) + 1); // Include null terminator
    }

    // Close sockets
    close(clientSocket);
    close(serverSocket);
    */

   
   
}