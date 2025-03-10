NAME = readmap

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c ft_openfile.c ft_readline.c ft_readfile.c ind_max_square.c write_text.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c fr_readmap.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
