#include "../include/Client.hpp"

Client::Client( int clientSocketFD, int clientPort, const string& hostName )
	: _clientSocketFD(clientSocketFD),
	_clientPort(clientPort),
	_hostName(hostName),
	_clientStatus(CLIENT_CONNECTED)
{
}

Client::~Client() {}

string Client::getPrefix() const
{
	string username = _userName.empty() ? "" : "!" + _userName;
	string hostname = _hostName.empty() ? "" : "@" + _hostName;

	return ":" + _nickName + username + hostname;
}

void Client::setNickName( const string& nickName ) {
	if (isValidName(nickName)) {
		_nickName = nickName;
	}
	else {
		cerr << "Invalid nickname: " << nickName << endl;
	}
}

void Client::setUserName( const string& userName ) {
	if (isValidName(userName)) {
		_userName = userName;
	}
	else {
		cerr << "Invalid username: " << userName << endl;
	}
}

void Client::welcomeMessage()
{
	if ( _clientStatus != CLIENT_CONNECTED || _nickName.empty() || _userName.empty() || _realName.empty() )
		return;

	_clientStatus = CLIENT_REGISTERED;
	sendReply(WELCOME_MESSAGE(_nickName));

	char buffer[100];
	sprintf(buffer, "%s:%d is now known as %s.", _hostName.c_str(), _clientPort, _nickName.c_str());
	log(buffer);
}

void Client::sendMessage( const string& message ) const
{
	string buffer = message + "\r\n";

	if (send(_clientSocketFD, buffer.c_str(), buffer.length(), 0) == -1) {
		ErrorLogger(FAILED_SOCKET_SEND, __FILE__, __LINE__);
	}
}

void Client::sendReply( const string& reply ) const
{
	sendMessage(getPrefix() + " " + reply);
}

void Client::leave()
{
	_clientStatus = CLIENT_DISCONNECTED;
}