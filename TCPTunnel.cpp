#include "TCPTunnel.h"
#include <stdexcept> // Para std::runtime_error

#ifdef _WIN32
  #include <winsock2.h>
  #pragma comment(lib, "ws2_32.lib")
#else
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h> // Se agrega la biblioteca
  #include <unistd.h>
#endif

// Constructor
TCPTunnel::TCPTunnel() : sockfd(-1) {
  // Inicializar aqu� los atributos necesarios
#ifdef _WIN32
  WSADATA wsaData;
  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    throw std::runtime_error("Error al inicializar Winsock");
  }
#endif
}

// Destructor
TCPTunnel::~TCPTunnel() {
  // Si el socket est� abierto, lo cerramos
  if (sockfd != -1) {
    disconnect();
  }
#ifdef _WIN32
  WSACleanup();
#endif
}

// M�todo para desconectar
void TCPTunnel::disconnect() {
  if (sockfd != -1) {
#ifdef _WIN32
    closesocket(sockfd);
#else
    close(sockfd);
#endif
    sockfd = -1;
  }
}

// M�todo para conectar
bool TCPTunnel::connect(const std::string& serverIP, int serverPort) {
  // Verificar los datos de entrada
  if (serverIP.empty() || serverPort <= 0 || serverPort > 65535) {
    throw std::runtime_error("Datos de entrada inv�lidos");
  }

  // Crear un socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    throw std::runtime_error("Error al crear el socket");
  }

  // Configurar la direcci�n del servidor
  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(serverPort);

  // Se corrige la linea que causa el error
  if (inet_pton(AF_INET, serverIP.c_str(), &(serv_addr.sin_addr)) <= 0) {
    throw std::runtime_error("Error al configurar la direcci�n del servidor");
  }

  // Establecer la conexi�n TCP con el servidor
  if (::connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
    throw std::runtime_error("Error al conectar con el servidor");
  }

  // Si llegamos hasta aqu�, la conexi�n se estableci� correctamente
  return true;
}

// M�todo para enviar datos
bool TCPTunnel::sendData(const std::string& data) {
    // Verificar los datos de entrada
    if (data.empty()) {
        throw std::runtime_error("Datos de entrada inv�lidos");
    }

    ssize_t bytesSent = send(sockfd, data.c_str(), data.size(), 0);
    if (bytesSent < 0) {
        throw std::runtime_error("Error al enviar datos");
    }
    return true;
}

// M�todo para recibir datos
std::string TCPTunnel::receiveData() {
    char buffer[1024];
    ssize_t bytesReceived = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived < 0) {
        throw std::runtime_error("Error al recibir datos");
    }
    buffer[bytesReceived] = '\0'; // Aseguramos que la cadena est� terminada en null
    return std::string(buffer);
}
