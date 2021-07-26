import socket
import time

localIP = "127.0.0.1"

localPort = 1342

bufferSize = 65535

msgFromServer = "Hello UDP Client"

bytesToSend = str.encode(msgFromServer)

# Create a datagram socket

UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

# Bind to address and ip

UDPServerSocket.bind((localIP, localPort))

print("UDP server up and listening")
# Listen for incoming datagrams

bytesAddressPair = UDPServerSocket.recvfrom(bufferSize)

message: bytes = bytesAddressPair[0]

client_address = bytesAddressPair[1]

clientMsg = "Message from Client:{}".format(message)
clientIP = "Client IP Address:{}".format(client_address)

print(clientMsg)
print(clientIP)

client_address = ("127.0.0.1", 1233)
while True:
    bytesAddressPair = UDPServerSocket.recvfrom(bufferSize)

    message: bytes = bytesAddressPair[0]

    print(message)

    UDPServerSocket.sendto(message, client_address)
