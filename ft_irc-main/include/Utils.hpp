#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <exception>
#include <fstream>


using namespace std;

#define GET_CURRENT_TIME time(0)
#define FORMAT_TIME(t, buffer) strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", localtime(&t))

/* SERVER FAILED/ERROR MESSAGES */
#define FAILED_SOCKET "Failed to create socket"
#define FAILED_SOCKET_OPTIONS "Failed to set socket options"
#define FAILED_SOCKET_NONBLOCKING "Failed to set socket to non-blocking"
#define FAILED_SOCKET_BIND "Failed to bind socket"
#define FAILED_SOCKET_LISTEN "Failed to listen socket"
#define FAILED_SOCKET_ACCEPT "Failed to accept socket"
#define FAILED_SOCKET_CONNECT "Failed to connect socket"
#define FAILED_SOCKET_SEND "Failed to send socket"
#define FAILED_SOCKET_RECV "Failed to recv socket"
#define FAILED_SOCKET_CLOSE "Failed to close socket"
#define FAILED_SOCKET_GETADDRINFO "Failed to getaddrinfo socket"
#define FAILED_SOCKET_DOMAIN "Not supported domain"
#define FAILED_SOCKET_POLL "Failed to poll socket"
#define FAILED_SOCKET_RECEIVE "Failed to receive socket"
#define FAILED_SOCKET_EPOLL "Failed to create epoll"
#define FAILED_SOCKET_EPOLL_CTL "Failed to add socket to epoll"
#define FAILED_SOCKET_KQUEUE "Failed to create kqueue"
#define FAILED_SOCKET_KQUEUE_KEVENT "Failed to add socket to kqueue"

/* SERVER DEFINE */
#define BACKLOG_SIZE 100
#define MAX_CLIENTS 100

/* CLIENT FAILED/ERROR MESSAGES */
#define ERROR_SOCKET_SEND "Error while sending a message to a client!"
	/* REPLY */
#define WELCOME_MESSAGE(source) "Welcome to the Internet Relay Network " + source + "!" + source + "@" + source

static inline void ErrorLogger( string messageInfo, const char* fileInfo, int lineInfo, bool isFatal = false )
{
	ofstream errorLog;

	errorLog.open("error.log", ios::app);
	errorLog << "Error Time: " << __TIME__ << endl;
	errorLog << "Error in file: " << fileInfo << ":" << lineInfo << endl;
	errorLog << "Error info: " << string(strerror(errno)) << endl;
	errorLog << "----------------------------------------" << endl;
	errorLog.close();

	if (isFatal) {
		throw runtime_error(messageInfo);
	}
	cerr << "Error: " << messageInfo << endl;
}

static inline void log( const string& message )
{
	char buffer[100];
	time_t currentTime = GET_CURRENT_TIME;
	ofstream logFile;

	FORMAT_TIME(currentTime, buffer);
	string time(buffer);

	logFile.open("log.log", ios::app);
	logFile << time << " " << message << endl;
	logFile.close();

	std::cout << "\033[0;34m[" << time << "]\033[0m ";
	std::cout << message << std::endl;
}

#endif
