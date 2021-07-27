import socket

msgFromClient = "Client1"

bytesToSend = str.encode(msgFromClient)

serverAddressPort = ("168.6.245.88", 1350)

bufferSize = 1024

# Create a UDP socket at client side

UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

# Send to server using created UDP socket

UDPClientSocket.sendto(bytesToSend, serverAddressPort)

print("message sent")

msgFromServer = UDPClientSocket.recvfrom(bufferSize)

msg = "Message from Server {}".format(msgFromServer[0])

print(msg)

#msg_to_client2 = "to client 2: hello client2"

#bytesToSend = str.encode(msg_to_client2)

#UDPClientSocket.sendto(bytesToSend, serverAddressPort)
