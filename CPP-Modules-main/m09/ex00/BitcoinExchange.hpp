#ifndef BITCOINEXCHANGE
# define BITCOINEXCHANGE

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <map>

class btc
{
	private:
		std::map<std::string, float>	_btc;
	public:
		void	setInput(char *argv);
		void	setDataBase(int argc);
		std::string	setInputDate(std::string date);

		inline float	getValue(std::string date, int begin);

		bool	checkInput (std::string date);
		bool	is_digits(const std::string &str){return str.find_first_not_of("0123456789") == std::string::npos;}//98
		void	printBitcoinExchange( std::string data);
		void	setInputValue(std::string date);

	class CoultNotOpenFile : public std::exception
	{
		public:
			const char*	what() const throw();
	};
	class InvalidFormat : public std::exception
	{
		public:
			const char*	what() const throw();
	};
};

#endif