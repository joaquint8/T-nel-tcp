import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('127.0.0.1', 8080))
server_socket.listen(1)

print('Servidor iniciado. Esperando conexiones...')

while True:
    client_socket, client_address = server_socket.accept()
    print('Conexión establecida desde', client_address)

    while True:
        data = client_socket.recv(1024)
        if not data:
            break
        print('Recibido:', data.decode('utf-8'))
        print('Enviando datos de vuelta al cliente...')
        client_socket.sendall(data)

    print('Conexión con', client_address, 'cerrada.')
    client_socket.close()

print('Servidor detenido.')