/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:43:09 by uercan            #+#    #+#             */
/*   Updated: 2023/04/07 16:05:44 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <iostream>
#include <ctime>
#include <iomanip>

int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

Account::Account( int initial_deposit )
{
	_accountIndex = getNbAccounts();
	_amount = initial_deposit;
	_nbDeposits = 0;
	_nbWithdrawals = 0;
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";";
	std::cout << "amount:" << _amount << ";created" << std::endl;
	_totalAmount += initial_deposit;
}

Account::~Account(void)
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";"
	<< "amount:" << _amount << ";closed" << std::endl;
}

int	Account::getNbAccounts( void )
{
	return (_nbAccounts++);
}

int	Account::getTotalAmount( void )
{
	return (_totalAmount);
}

int	Account::getNbDeposits( void )
{
	return (_totalNbDeposits++);
}

int	Account::getNbWithdrawals(void)
{
	return (_totalNbWithdrawals++);
}

void	Account::displayAccountsInfos( void )
{
	_displayTimestamp();
	std::cout << "accounts:" << _nbAccounts
	<< ";total:" << _totalAmount
	<< ";deposits:" << _totalNbDeposits
	<< ";withdrawals:" << _totalNbWithdrawals<< std::endl;
}

void	Account::makeDeposit(int deposit)
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";";
	std::cout << "p_amount:" << _amount << ";";
	std::cout << "deposit:" << deposit << ";";
	std::cout << "amount:" << _amount + deposit << ";";
	std::cout << "nb_deposit:" << ++_nbDeposits << std::endl;
	_totalAmount += deposit;
	_amount += deposit;
}

void	Account::displayStatus(void) const
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";";
	std::cout << "amount:" << _amount << ";";
	std::cout << "deposits:" << _nbDeposits << ";";
	std::cout << "withdrawals:" << _nbWithdrawals << std::endl;
}

bool	Account::makeWithdrawal(int withdrawal)
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";";
	std::cout << "p_amount:" << _amount << ";";
	if (withdrawal <= _amount && withdrawal > 0)
	{
		std::cout << "withdrawal:" << withdrawal << ";";
		std::cout << "amount:" << _amount - withdrawal << ";";
		std::cout << "nb_withdrawals:" << ++_nbWithdrawals << std::endl;
		_totalAmount -= withdrawal;
		_amount -= withdrawal;
		return (true);
	}
	std::cout << "refused" << std::endl;
	return (false);
}

int	Account::checkAmount(void) const
{
	return (0);
}

void	Account::_displayTimestamp(void)
{
	std::time_t	time;

	time = std::time(NULL);
	std::cout << std::setfill('0') << "["
		<< std::setw(2) << 1900 + std::localtime(&time)->tm_year
		<< std::setw(2) << 1 +  std::localtime(&time)->tm_mon
		<< std::setw(2) << std::localtime(&time)->tm_mday << "_"
		<< std::setw(2) << std::localtime(&time)->tm_hour
		<< std::setw(2) << std::localtime(&time)->tm_min
		<< std::setw(2) << std::localtime(&time)->tm_sec
		<< "] ";
}
