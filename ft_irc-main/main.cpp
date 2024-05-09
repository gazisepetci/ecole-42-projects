#include "include/Server.hpp"

int main()
{
	try
	{
		Server srv(AF_INET, SOCK_STREAM, 6674);
		srv.serverRun();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
}
