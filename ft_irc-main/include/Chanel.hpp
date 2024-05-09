#ifndef CHANEL_HPP
#define CHANEL_HPP

#include <vector>

#include "Client.hpp"
#include "Server.hpp"

class Chanel
{
	private:
		string _chanelName;
		vector<Client*> _clients;
		Client* _chanelOwner;

		/* MODES */
		string _chanelKey;
		size_t _chanelLimit;
		bool _chanelPrivate;

		Chanel();
		Chanel( const Chanel& copy );
	public:
		Chanel ( const string& chanelName, const string& chanelKey, Client* chanelOwner );
		~Chanel();

		/* GETTERS */
		string getChanelName() const { return _chanelName; }
		Client* getChanelOwner() const { return _chanelOwner; }

		string getChanelKey() const { return _chanelKey; }
		size_t getChanelLimit() const { return _chanelLimit; }
		bool isChanelPrivate() const { return _chanelPrivate; }

		size_t getChanelClientCount() const { return _clients.size(); }
		vector<string> getChanelClientNickNames() const;

		/* SETTERS */
		void setChanelKey( const string& chanelKey ) { _chanelKey = chanelKey; }
		void setChanelLimit( size_t chanelLimit ) { _chanelLimit = chanelLimit; }
		void setChanelPrivate( bool chanelPrivate ) { _chanelPrivate = chanelPrivate; }

		/* ACTIONS */
		void broadcastMessage( const string& message ) const;
		void broadcastMessage( const string& message, Client* exceptClient ) const;

		void addClient( Client* client );
		void removeClient( Client* client );
		void kickClient( Client* client, Client* target, const string& reason = "" );
};

#endif