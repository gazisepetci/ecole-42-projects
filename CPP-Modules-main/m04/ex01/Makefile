NAME	= Animal

CC		= c++
FLAGS	= -Wall -Wextra -Werror -std=c++98 -Wshadow -Wno-shadow 
RM		= rm -rf

all: $(NAME)

$(NAME): *.cpp *.hpp
	@ $(CC) $(FLAGS) *.cpp -o $(NAME)

clean:
	@$(RM) $(NAME)

fclean:
	@$(RM) $(NAME)

re: clean all

run: fclean all
	clear
	./$(NAME)

.PHONY: all clean re run