SRC = src/main.c \
	parse/parse.c \

CFLAGS = -Wall -Wextra -Werror
CC = clang

NAME = minishell

OBJ = $(SRC:.c=.o)

Libft = libft/libft.a

LIBFT_PATH = ./libft/

GREEN = \033[32m

YELLOW = "\033[33m"

INCLUDE = -I ./includes/ \

READLINE = -lreadline

nb:=1

all: $(NAME)

.c.o :
	@echo -n $(YELLOW)
	@$(CC)  $(INCLUDE) $(CFLAGS) -c $< -o $(<:.c=.o)
	@echo -n "\r[ Compiling " ${nb} "\ 1 Objects ]"
	$(eval nb=$(shell echo $$(($(nb)+1))))

$(NAME): $(OBJ)
	@echo -n "\n"
	@make -C libft
	@$(CC) $(OBJ) $(READLINE)  $(Libft) $(CFLAGS) -o $(NAME) $(INCLUDE)
	@echo "$(GREEN)	\nMINISHELL READY 💪!"


clean:
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean


.PHONY: all re fclean clean

re: flcean all