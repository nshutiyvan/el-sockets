
CR="arm-linux-gcc"
CC="gcc"
FLAGS="-Wall -Wextra"



.PHONY:clean





clean:
	rm -rf cceptTCPConnection.o Auxiliary.o CreateTCPClientSocket.o AcceptTCPConnection.o CreateTCPServerSocket.o getaddrinfo.o HandleTCPClient.o TCPEchoClient.o TCPEchoServer-Fork.o TCPEchoServer.o TCPEchoServer-Thread.o TCPEchoClient TCPEchoServer-Fork TCPEchoServer TCPEchoServer-Thread
