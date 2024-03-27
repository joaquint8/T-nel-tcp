#include <iostream>
#include "TCPTunnel.h"
#pragma comment(lib, "ws2_32.lib")

int main() {
    TCPTunnel tunnel;

    try {
        // Intentamos establecer una conexi�n
        if (tunnel.connect("127.0.0.1", 8080)) { // Reemplaza 'localhost' y '8080' con la direcci�n IP y el puerto de tu servidor
            std::cout << "Conexi�n establecida con �xito" << std::endl;

            // Enviamos y recibimos datos
            tunnel.sendData("Hola, mundo!");
            std::string data = tunnel.receiveData();
            std::cout << "Recibido: " << data << std::endl;

            // Cuando hayas terminado, cierras la conexi�n
            tunnel.disconnect();
            std::cout << "Conexi�n cerrada con �xito" << std::endl;
        }
    } catch (const std::runtime_error& e) {
        // Si ocurre una excepci�n, la atrapamos aqu� y mostramos el mensaje de error
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
