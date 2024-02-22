CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
NAME = my_htop
SRC = main.c list.c sort.c
OBJ = $(SRC:.c=.o)
LIBS = -lncurses

all: $(NAME)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: re
	./$(NAME)

.PHONY: all clean fclean re