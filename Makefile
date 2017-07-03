all: sicherServer.cpp
	g++ -Wall -pthread sicherServer.cpp -o sicherServer
