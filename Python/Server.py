import socket
import time

localIP = "168.6.245.88"
localPort = 1234
client_address = ("10.238.200.106", 1233)
bufferSize = 3000
forwarding = False

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

if not forwarding:
    client_address = bytesAddressPair[1]

clientMsg = "Message from Client:{}".format(message)
clientIP = "Client IP Address:{}".format(client_address)

print(clientMsg)
print(clientIP)


while True:
    bytesAddressPair = UDPServerSocket.recvfrom(bufferSize)
    message: bytes = bytesAddressPair[0]
    print(message)
    UDPServerSocket.sendto(message, client_address)
