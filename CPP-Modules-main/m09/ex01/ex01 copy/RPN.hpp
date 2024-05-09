#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <stack>
#include <cstdlib>// -!-

void	setArgument(char *argv);
void	calculateValue (std::stack<int> *Stack);
bool	checkArgument(std::string argv);
bool	checkBigNumbers(std::string argv);

#endif
