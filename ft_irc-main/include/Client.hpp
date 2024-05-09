#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <sys/socket.h>
#if defined(__linux__)
#include <sys/epoll.h>
#endif
#if defined(__APPLE__) || defined(__MACH__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined (__NetBSD__)
#include <sys/event.h>
#endif

#include <iostream>

#include "Utils.hpp"
#include "Chanel.hpp"

using namespace std;

enum ClientStatus
{
	CLIENT_HANDSHAKING,
	CLIENT_CONNECTED,
	CLIENT_REGISTERED,
	CLIENT_DISCONNECTED
};

class Client
{
private:
	int _clientSocketFD;
	int _clientPort;

	string _nickName;
	string _userName;
	string _realName;
	string _hostName;

	ClientStatus _clientStatus;
	Chanel* _chanel;

	Client();
	Client( const Client& copy );
	Client& operator=( const Client& copy );

	bool isValidName( const string& name ) const
	{
		const int MAX_LENGTH = 9;  // IRC standartlarında genel bir sınır
		if (name.length() > MAX_LENGTH) {
			return false;
		}

		for (std::string::const_iterator it = name.begin(); it != name.end(); ++it) {
			if (!isalnum(*it)) {
				return false;
			}
		}

		return true;
	}
public:
	Client( int clientSocketFD, int clientPort, const string& hostName );
	~Client();

	/* GETTERS */
	int getClientSocketFD() const { return _clientSocketFD; }
	int getClientPort() const { return _clientPort; }

	string getNickName() const { return _nickName; }
	string getUserName() const { return _userName; }
	string getRealName() const { return _realName; }
	string getHostName() const { return _hostName; }
	string getPrefix() const;

	bool isRegistered() const { return _clientStatus == CLIENT_REGISTERED; }

	Chanel* getChanel() const { return _chanel; }

	/* SETTERS */
	void setNickName( const string& nickName );
	void setUserName( const string& userName );
	void setRealName( const string& realName ) { _realName = realName; }
	void setStatus( ClientStatus clientStatus ) { _clientStatus = clientStatus; }
	void setChanel( Chanel* chanel ) { _chanel = chanel; }

	/* ACTIONS */
	void welcomeMessage();

	void sendMessage( const string& message ) const;
	void sendReply( const string& reply ) const;

	void leave();

	
};

#endif
