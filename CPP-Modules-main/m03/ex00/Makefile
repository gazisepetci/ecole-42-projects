NAME	= ClapTrap

CC		= c++
FLAGS	= -Wall -Wextra -Werror -std=c++98
RM		= rm -rf

all: $(NAME)

$(NAME):
	@ $(CC) $(FLAGS) *.cpp -o $(NAME)

clean:
	@$(RM) $(NAME)

fclean:
	@$(RM) $(NAME)

re: clean all

run: re
	clear
	./$(NAME)

.PHONY: all clean re