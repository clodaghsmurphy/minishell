SRC = src/main.c \
	parse/parse.c \

NO_OF_FILES := $(words $(SRC)) 

CFLAGS = -Wall -Wextra -Werror
CC = clang

NAME = minishell

OBJ = $(SRC:.c=.o)

Libft = libft/libft.a

LIBFT_PATH = ./libft/

GREEN = "\033[1;32m"

YELLOW = "\033[1;33m"

INCLUDE = -I ./includes/ \

READLINE = -lreadline

nb:=1

all: $(NAME)





.c.o :
	@$(CC)  $(INCLUDE) $(CFLAGS) -c $< -o $(<:.c=.o)
	@echo -n $(YELLOW)
	@echo -n "\r[Compiling $(nb) / $(NO_OF_FILES) Minishell Objects]"
	$(eval nb=$(shell echo $$(($(nb)+1))))


$(NAME): $(OBJ)
	@echo -n $(GREEN)
	@echo "\n	DONE ✅\n"
	@echo -n $(YELLOW)
	@echo -n "\nCOMPILING LIBFT"
	@make -C libft
	@echo -n $(YELLOW)
	@$(CC) $(OBJ) $(READLINE)  $(Libft) $(CFLAGS) -o $(NAME) $(INCLUDE)
	@echo $(GREEN)	"MINISHELL READY 💪!"


clean:
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean


.PHONY: all re fclean clean

re: flcean all