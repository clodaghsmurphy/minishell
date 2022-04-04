NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = ft_memset.c\
      ft_bzero.c\
      ft_memcpy.c\
      ft_memccpy.c\
      ft_memmove.c\
      ft_memchr.c\
      ft_memcmp.c\
      ft_atoi.c\
      ft_itoa.c\
      ft_strlen.c\
      ft_isalpha.c\
      ft_isdigit.c\
      ft_isascii.c\
      ft_isprint.c\
      ft_isalnum.c\
      ft_strlcat.c\
      ft_strchr.c\
      ft_strrchr.c\
      ft_toupper.c\
      ft_tolower.c\
      ft_strnstr.c\
      ft_strncmp.c\
      ft_strlcpy.c\
      ft_strdup.c\
      ft_calloc.c\
      ft_substr.c\
      ft_strjoin.c\
      ft_strtrim.c\
      ft_putchar_fd.c\
      ft_putstr_fd.c\
      ft_putendl_fd.c\
      ft_putnbr_fd.c\
      ft_strmapi.c\
      ft_split.c\
      ft_striteri.c

BONUS	=     ft_lstnew.c \
            ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
	      ft_lstmap.c \
            
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	ar crs $@ $^

bonus:
			$(CC) $(CFLAGS) -c $(SRC) $(BONUS)
			ar rc $(NAME) $(OBJ) $(BONUS:.c=.o)

%.o : %.c
	$(CC) -o $@ -c $^ $(CFLAGS) 

clean :
	rm -rf *.o

fclean : clean
	rm -rf $(NAME)

re : fclean all

