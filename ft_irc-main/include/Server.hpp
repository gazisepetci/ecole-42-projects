#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#if defined(__linux__)
#include <sys/epoll.h>
#endif
#if defined(__APPLE__) || defined(__MACH__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined (__NetBSD__)
#include <sys/event.h>
#endif
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <map>

#include "Utils.hpp"
#include "Client.hpp"

class Client;

using namespace std;

class Server
{
	private:
		int _serverSocketFD;
		const int _serverSocketFamily; // IPV4 V6 etc..
		const int _serverSocketProtocol; // TCP/IP - UDP
		const int _serverSocketPort; // 1234 2345 etc..


		struct sockaddr_in serverAddress;
		struct sockaddr_in6 serverAddress6;


#if defined(__linux__)
		int epollFd;
#elif defined(__APPLE__) || defined(__MACH__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined (__NetBSD__)
		int kq;
#endif

		map<int, Client*> _clients;

		void socketStart();
		void socketInit();
		void socketBind();
		void socketListen();
		int socketAccept();

		void handleClient(int clientSocketFD);
		void clientDisconnect(int clientSocketFD);
	public:
		Server ( int serverSocketFamily, int serverSocketProtocol, int serverSocketPort );
		~Server();


		void serverRun();
};

#endif
