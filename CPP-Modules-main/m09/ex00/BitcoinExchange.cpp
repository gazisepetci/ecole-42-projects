#include "BitcoinExchange.hpp"

bool	btc::checkInput(std::string date)
{
	if (is_digits(date.substr(0,4))
		&& is_digits(date.substr(5,2))
		&& is_digits(date.substr(8,2))
		&& atoi(date.substr(0, 4).c_str()) > 2008
		&& atoi(date.substr(0, 4).c_str()) < 2023
		&& atoi(date.substr(5, 2).c_str()) > 0
		&& atoi(date.substr(5, 2).c_str()) < 13
		&& atoi(date.substr(8, 2).c_str()) < 32
		&& atoi(date.substr(8, 2).c_str()) > 0
		&& date[4] == '-'
		&& date[7] == '-'
		&& date[11] == '|')
	{
		if (atoi(date.substr(0, 4).c_str()) == 2009
		&& atoi(date.substr(5, 2).c_str()) == 1
		&& atoi(date.substr(8, 2).c_str()) < 2)
			std::cout << "Error: bad input => " << date.substr(0,10) << std::endl;
		else if (std::strtol(date.substr(13,date.length()).c_str(), nullptr, 10) > -1)
		{
			if (std::strtol(date.substr(13,date.length()).c_str(), nullptr, 10) <= 1000)
				return (true);
			else
				std::cout << "Error: too large a number." << std::endl;
		}
		else
				std::cout << "Error: not a positive number." << std::endl;
	}
	else
	{
		std::cout << "Error: bad input => " << date.substr(0,10) << std::endl;
		return (false);
	}
	return (false);
}

void	btc::setInput(char *argv)
{
	try{
		std::map<std::string, float>::iterator upperBoundIter;
		std::ifstream	f_read((std::string)argv);
		std::string		line;
		float			value;
		if (f_read.is_open())
		{
			while (getline (f_read,line))
			{
				if (line != "date | value" && checkInput(line))
				{
					upperBoundIter = this->_btc.upper_bound(line.substr(0, 10));
					if (upperBoundIter != this->_btc.end())
					{
						value = getValue(line, 13);
						--upperBoundIter;
						std::cout << line.substr(0, 10) << " => " << value << " = " << value * upperBoundIter->second << std::endl;
					}
				}
			}
			f_read.close();
		}
		else
			throw(btc::CoultNotOpenFile());
	}catch(std::exception &e){
		std::cout << e.what() << std::endl;
	}
}

inline float	btc::getValue(std::string date, int begin)
{
	return (strtof(date.substr(begin,date.length()).c_str(), nullptr));
}

void	btc::setDataBase(int argc)
{
	if (argc != 2)
		throw(btc::CoultNotOpenFile());
	std::ifstream	f_read("data.csv");
	std::string		line;
	if (f_read.is_open())
	{
		while (getline (f_read,line))
			if (is_digits(line.substr(0,4)) && line != "date,exchange_rate")
				this->_btc.insert(std::make_pair(line.substr(0,10), getValue(line, 11)));
		f_read.close();
	}
	else
		throw(btc::CoultNotOpenFile());
}

const char	*btc::CoultNotOpenFile::what() const throw()
{
	return ("Error: Coult not open file");
}

const char	*btc::InvalidFormat::what() const throw()
{
	return ("Error: Invalid format");
}
