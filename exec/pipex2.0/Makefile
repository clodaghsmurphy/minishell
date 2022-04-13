NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = pipex.c \
	utils.c \
	ft_split.c \
	ft_strncmp.c \
	ft_strlen.c \
	ft_strjoin.c \
	errors.c \
	ft_strdup.c \
		
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.c
	$(CC) -o $@ -c $^ $(CFLAGS)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

