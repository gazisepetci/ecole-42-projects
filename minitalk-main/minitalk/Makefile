# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uercan <uercan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/23 10:09:04 by gsepetci          #+#    #+#              #
#    Updated: 2022/07/03 14:59:20 by uercan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@gcc -Wall -Wextra -Werror server.c ft_putnbr.c -o server
	@gcc -Wall -Wextra -Werror client.c ft_atoi.c -o client

clean:
	@rm -f server
	@rm -f client

fclean: clean

re: fclean all

.PHONY:all clean fclean re