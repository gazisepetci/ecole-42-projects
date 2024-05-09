#include "../include/Chanel.hpp"

Chanel::Chanel( const string& chanelName, const string& chanelKey, Client* chanelOwner )
	: _chanelName(chanelName),
	_chanelOwner(chanelOwner),
	_chanelKey(chanelKey),
	_chanelLimit(0),
	_chanelPrivate(false)
{
}

Chanel::~Chanel() {}

vector<string> Chanel::getChanelClientNickNames() const
{
	vector<string> nickNames;
	for (vector<Client*>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
		string nickName = (*it == _chanelOwner ? "@" : "") + (*it)->getNickName();
		nickNames.push_back(nickName);
	}

	return nickNames;
}

void Chanel::broadcastMessage( const string& message ) const
{
	for (vector<Client*>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
		(*it)->sendMessage(message);
	}
}

void Chanel::broadcastMessage( const string& message, Client* exceptClient ) const
{
	for (vector<Client*>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (*it != exceptClient) {
			(*it)->sendMessage(message);
		}
	}
}

void Chanel::addClient( Client* client )
{
	_clients.push_back(client);
}

void Chanel::removeClient( Client* client )
{
	for (vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (*it == client) {
			_clients.erase(it);
			return;
		}
	}
}