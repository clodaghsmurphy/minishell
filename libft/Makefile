NAME = libft.a
CC = gcc
GREEN = \033[1;32m
YELLOW = "\033[1;33m"
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I ../includes/ 
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

NO_OF_FILES := $(words $(SRC))

MAKE = make --silent --jobs

all : $(NAME)

.c.o:
	@$(CC) $(CFLAGS) -g -c $< -o $(<:.c=.o)
	$(eval nb=$(shell echo $$(($(nb)+1))))
	@echo -n $(YELLOW)
	@echo -n $(YELLOW)" \r[Compiling $(nb) / $(NO_OF_FILES) Libft Objects]"
	@echo -n $(YELLOW)


$(NAME) : $(OBJ)
	@ar -crs $(NAME)  $(OBJ)
	@echo -n "$(GREEN)	\n>>>>>>>>>>>>>>>>LIBFT READY! ✅<<<<<<<<<<<<<<<<<<\n"
	@echo -n "\n"
	@echo -n $(YELLOW)

bonus:
	@$(CC) $(INCLUDE) $(CFLAGS) -c $(SRC) $(BONUS)
	@ar rc $(NAME) $(OBJ) $(BONUS:.c=.o)

clean :
	@rm -rf *.o

fclean : clean
	@rm -rf $(NAME)

re : fclean all

