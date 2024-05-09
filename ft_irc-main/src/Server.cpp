#include "../include/Server.hpp"

Server::Server(int serverSocketFamily, int serverSocketProtocol, int serverSocketPort)
	: _serverSocketFD(-1),
	_serverSocketFamily(serverSocketFamily),
	_serverSocketProtocol(serverSocketProtocol),
	_serverSocketPort(serverSocketPort)
{
	memset(&serverAddress, 0, sizeof(serverAddress));
	memset(&serverAddress6, 0, sizeof(serverAddress6));

#if defined(__linux__)
	epollFd = epoll_create1(0);
	if (epollFd == -1) {
		// Hata işleme...
	}
#elif defined(__APPLE__) || defined(__MACH__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined (__NetBSD__)
	kq = kqueue();
	if (kq == -1) {
		// Hata işleme...
	}
#endif
}

Server::~Server()
{
	if (_serverSocketFD != -1)
	{
		close(_serverSocketFD);
	}
#if defined(__linux__)
	if (epollFd != -1)
	{
		close(epollFd);
	}
#elif defined(__APPLE__) || defined(__MACH__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined (__NetBSD__)
	if (kq != -1)
	{
		close(kq);
	}
#endif
}

void Server::socketStart()
{
	_serverSocketFD = socket( _serverSocketFamily, _serverSocketProtocol, 0 );

	if ( _serverSocketFD == -1 )
		ErrorLogger( FAILED_SOCKET, __FILE__, __LINE__ );

	if ( fcntl(_serverSocketFD, F_SETFL, O_NONBLOCK) == -1 )
	{
		close(_serverSocketFD);
		ErrorLogger( FAILED_SOCKET_NONBLOCKING, __FILE__, __LINE__ );
	}

	int reuse = 1;
	if ( setsockopt(_serverSocketFD, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1 )
	{
		close(_serverSocketFD);
		ErrorLogger( FAILED_SOCKET_OPTIONS, __FILE__, __LINE__ );
	}

}

void Server::socketInit()
{
	switch ( _serverSocketFamily )
	{
		case AF_INET:
			serverAddress.sin_addr.s_addr = INADDR_ANY;
			serverAddress.sin_family = _serverSocketFamily;
			serverAddress.sin_port = htons( _serverSocketPort );
			break;
		case AF_INET6:
			serverAddress6.sin6_addr = in6addr_any;
			serverAddress6.sin6_family = _serverSocketFamily;
			serverAddress6.sin6_port = htons( _serverSocketPort );
			break;
		default:
			close(_serverSocketFD);
			ErrorLogger( FAILED_SOCKET_DOMAIN, __FILE__, __LINE__ );
	}
}

void Server::socketBind()
{
	switch (_serverSocketFamily)
	{
		case AF_INET: {
			if ( ::bind(_serverSocketFD, reinterpret_cast<struct sockaddr *>(&serverAddress), sizeof(serverAddress)) == -1 )
			{
				close(_serverSocketFD);
				ErrorLogger(FAILED_SOCKET_BIND, __FILE__, __LINE__);
			}
			break;
		}
		case AF_INET6:
		{
			if ( ::bind(_serverSocketFD, reinterpret_cast<struct sockaddr *>(&serverAddress6), sizeof(serverAddress6)) == -1 )
			{
				close(_serverSocketFD);
				ErrorLogger(FAILED_SOCKET_BIND, __FILE__, __LINE__);
			}
			break;
		}
	}
}

void Server::socketListen()
{
	if ( listen(_serverSocketFD, BACKLOG_SIZE) == -1 )
	{
		close(_serverSocketFD);
		ErrorLogger(FAILED_SOCKET_LISTEN, __FILE__, __LINE__);
	}

#if defined(__linux__)
	struct epoll_event ev;
	ev.events = EPOLLIN; // Yeni bağlantılar için EPOLLIN yeterlidir.
	ev.data.fd = _serverSocketFD;  // server soket file descriptor

	if (epoll_ctl(epollFd, EPOLL_CTL_ADD, _serverSocketFD, &ev) == -1)
	{
		perror("epoll_ctl: server socket");
		// exit(EXIT_FAILURE);
	}
#elif defined(__APPLE__) || defined(__MACH__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined (__NetBSD__)
	struct kevent evSet;
	EV_SET(&evSet, _serverSocketFD, EVFILT_READ, EV_ADD, 0, 0, NULL);

	if (kevent(kq, &evSet, 1, NULL, 0, NULL) == -1)
	{
		perror("kevent: server socket");
		// exit(EXIT_FAILURE);
	}
#endif
}

int Server::socketAccept()
{
	struct sockaddr_storage clientAddress; // hem IPv4 hem de IPv6 adresleri için yeterince büyük
	socklen_t clientAddressLength = sizeof(clientAddress);

	int clientSocketFD = accept(_serverSocketFD, (struct sockaddr *)&clientAddress, &clientAddressLength);

	if (clientSocketFD < 0)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)
		{

		}
		else
		{
			ErrorLogger(FAILED_SOCKET_ACCEPT, __FILE__, __LINE__, true);
		}
	}
#if defined(__linux__)
	struct epoll_event event;
	event.data.fd = clientSocketFD;
	event.events = EPOLLIN | EPOLLET; // Edge-triggered read

	if (epoll_ctl(epollFd, EPOLL_CTL_ADD, clientSocketFD, &event) == -1)
	{
		close(clientSocketFD);
		ErrorLogger(FAILED_SOCKET_EPOLL_CTL, __FILE__, __LINE__);
	}
#elif defined(__APPLE__) || defined(__MACH__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined (__NetBSD__)
	struct kevent evSet;
	EV_SET(&evSet, clientSocketFD, EVFILT_READ, EV_ADD, 0, 0, NULL);

	if (kevent(kq, &evSet, 1, NULL, 0, NULL) == -1)
	{
		close(clientSocketFD);
		ErrorLogger(FAILED_SOCKET_KQUEUE_KEVENT, __FILE__, __LINE__);
	}
#endif
	// İstemci adresinden hostname alınması
	char hostname[NI_MAXHOST];
	if (getnameinfo((struct sockaddr *)&clientAddress, clientAddressLength, hostname, NI_MAXHOST, NULL, 0, NI_NUMERICSERV) != 0)
	{
		strcpy(hostname, "Unknown"); // Eğer hostname alınamazsa
	}

	// Yeni istemci nesnesinin oluşturulması ve saklanması
	Client* client = new Client(clientSocketFD, ntohs(((struct sockaddr_in*)&clientAddress)->sin_port), hostname);
	_clients.insert(std::make_pair(clientSocketFD, client));

	// Bağlantı mesajının günlüğe kaydedilmesi
	char message[2028];
	sprintf(message, "%s:%d has connected.", hostname, ntohs(((struct sockaddr_in*)&clientAddress)->sin_port));

	log(message);

	return clientSocketFD;
}

void Server::handleClient(int clientSocketFD)
{
	// Bu örnekte, basit bir buffer kullanıyoruz.
	char buffer[512];
	memset(buffer, 0, sizeof(buffer));

	ssize_t received = recv(clientSocketFD, buffer, sizeof(buffer), 0);
	if (received > 0) {
		// Veriyi aldık, işlememiz gerekiyor.
		// Örneğin, buffer'daki komutları ayrıştırabilir ve cevaplayabiliriz.
		std::cout << "Received message from client " << clientSocketFD << ": " << buffer;

		// Gelen mesaja göre eylem yapın (mesajı yorumlayın ve uygun komutları işleyin)
		// İstemciye cevap gönder
		const char* response = "Mesajınız alındı\n";
		ssize_t sent = send(clientSocketFD, response, strlen(response), 0);
		if (sent == -1) {
			// Gönderme hatası
			std::cerr << "Error sending response to client." << std::endl;
		}
	} else if (received == 0) {
		// Istemci bağlantıyı kapattı.
		clientDisconnect(clientSocketFD);
		// Bağlantıyı istemci listesinden çıkarın (eğer varsa).
	} else {
		// Hata alındı.
		if (errno != EAGAIN && errno != EWOULDBLOCK) {
			ErrorLogger("recv error", __FILE__, __LINE__);
			close(clientSocketFD); // Soketi kapatın.
			// Bağlantıyı istemci listesinden çıkarın (eğer varsa).
		}
	}
}

void Server::clientDisconnect(int clientSocketFD)
{
	try
	{
		std::map<int, Client*>::iterator it = _clients.find(clientSocketFD);
		if (it == _clients.end()) {
			std::cout << "Client with FD " << clientSocketFD << " not found." << std::endl;
			return;
		}

		Client* client = it->second;

		// İstemcinin ayrılması
		client->leave();

		// Bağlantının kesilmesi hakkında günlüğe kayıt
		char message[1000];
		sprintf(message, "%s:%d has disconnected!", client->getHostName().c_str(), client->getClientPort());
		log(message);

		// İstemciyi map'ten silme
		_clients.erase(it);

		// Soketi epoll veya kqueue'dan kaldırma
#if defined(__linux__)
		// epoll'dan kaldırma
		epoll_ctl(epollFd, EPOLL_CTL_DEL, clientSocketFD, NULL);
#elif defined(__APPLE__) || defined(__MACH__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined (__NetBSD__)
		// kqueue'dan kaldırma
		struct kevent evSet;
		EV_SET(&evSet, clientSocketFD, EVFILT_READ, EV_DELETE, 0, 0, NULL);
		kevent(kq, &evSet, 1, NULL, 0, NULL);
#endif

		// Soketi kapatma ve hafızayı serbest bırakma
		close(clientSocketFD);
		delete client;
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error while disconnecting client: " << e.what() << std::endl;
	}
}

void Server::serverRun()
{
	socketStart();
	socketInit();
	socketBind();
	socketListen();

	// Sunucunun ana döngüsü
	while (true)
	{
		// `epoll` veya `kqueue` ile mevcut bağlantıları dinleyin ve yeni bağlantıları kabul edin.
		// Bu örnek sadece `epoll` için yazılmıştır. `kqueue` için benzer bir yaklaşım uygulanmalıdır.
#if defined(__linux__)
		struct epoll_event events[MAX_CLIENTS]; // MAX_EVENTS tanımlanmalıdır.
		int n = epoll_wait(epollFd, events, MAX_CLIENTS, -1);
		for (int i = 0; i < n; i++) {
			if (events[i].data.fd == _serverSocketFD) {
				// Yeni bir bağlantıyı kabul edin.
				int clientFD = socketAccept();
				if (clientFD != -1) {
					// Yeni bağlantıyı işleyin (örneğin, bir liste/map'e ekleyin)
				}
			} else {

				if (events[i].events & EPOLLIN) {
					// Okunabilir veri var, istemciyi işleyin
					handleClient(events[i].data.fd);
				}
			}
		}
#elif defined(__APPLE__) || defined(__MACH__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined (__NetBSD__)
		struct kevent evList[MAX_CLIENTS];
		int n = kevent(kq, NULL, 0, evList, MAX_CLIENTS, NULL);
		for (int i = 0; i < n; i++) {
			if (evList[i].ident == _serverSocketFD) {
				// Yeni bir bağlantıyı kabul edin.
				int clientFD = socketAccept();
				if (clientFD != -1) {
					// Yeni bağlantıyı işleyin (örneğin, bir liste/map'e ekleyin)
				}
			} else {
				// Mevcut bir istemciden veri alındı.
				handleClient(evList[i].ident);
			}
		}
#endif
	}
}
