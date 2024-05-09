# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysensoy <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/04 19:33:29 by ysensoy           #+#    #+#              #
#    Updated: 2022/02/18 12:06:58 by ysensoy          ###   ########.tr        #
#                                                                              #
# **************************************************************************** #

NAME	:= libft.a
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror -I. -c
FILES	:= $(shell find . -type f ! -name "ft_lst*.c" -name "ft_*.c")
OBJ		:= $(FILES:%.c=%.o)

BSRC	:= $(wildcard ft_lst*.c)
B_OBJ	:= $(BSRC:%.c=%.o)

all:	$(NAME)

$(NAME): $(OBJ)
	ar	-rcs $(NAME) $(OBJ)

bonus:	$(OBJ) $(B_OBJ)
	ar	-rcs $(NAME) $(OBJ) $(B_OBJ)

clean:
	@rm -f *.o

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all	bonus clean fclean re
