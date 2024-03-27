## **Descripcion**
  Servidor TCP que sirve para la comunicacion cliente/servidor, se puede enviar/recibir pudiendo establecer una conexion con el servidor cuando se quiere enviar o recibir un mensaje y cerrando la misma cuando ya no se utiliza. 
## **¿Como funciona?**
El código se divide en tres partes principales:

* **TCPTunnel.h y TCPTunnel.cpp:** Estos archivos definen la clase TCPTunnel, que proporciona métodos para establecer conexiones TCP, enviar y recibir datos, y desconectar. Utiliza la biblioteca Boost.Asio para operaciones de red.

* **prueba.cpp:** Esta es la aplicación cliente que demuestra cómo usar la clase TCPTunnel. Crea un objeto TCPTunnel, se conecta a un servidor en "localhost" (127.0.0.1) en el puerto 8080, envía el mensaje "Hola, mundo!", recibe una respuesta del servidor (que es simplemente un eco de los datos enviados en este ejemplo), y luego se desconecta.

* **servidor.py:** Este script de Python implementa un servidor TCP simple que escucha en el puerto 8080. Acepta conexiones entrantes, recibe datos de los clientes y envía un eco de los datos recibidos al cliente.
## *Como utilizarlo*

  * Para ejecutarlo primero tiene que estar corriendo el servidor de python
  * Luego en una terminal, nos ubicamos dentro de la carpeta donde se encuentran los archivos ingresamos el comando: **./a.out**
