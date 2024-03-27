#ifndef TCPTUNNEL_H
#define TCPTUNNEL_H

#include <string>

class TCPTunnel {
public:
    TCPTunnel(); // Constructor
    ~TCPTunnel(); // Destructor

    bool connect(const std::string& serverIP, int serverPort);
    void disconnect();
    bool sendData(const std::string& data);
    std::string receiveData();

private:
    int sockfd; // Descriptor del socket
};

#endif
