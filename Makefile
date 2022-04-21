SRC = src/main.c \
	src/init.c \
	src/arm_signals.c \
	parse/parse.c \
	parse/split.c \
	parse/split_utils.c \
	parse/word_utils.c \
	parse/env_list.c \
	parse/env.c \
	parse/command_utils.c \
	parse/assign_tokens.c \
	parse/parse_vars.c \
	builtins/cd_pwd.c \
	builtins/echo.c \
	builtins/exit.c \
	builtins/export_utils.c \
	builtins/unset.c \
	exec/exec.c \
	exec/utils.c\


NO_OF_FILES := $(words $(SRC)) 

CFLAGS =# -Wall -Wextra -Werror
CC = clang

NAME = minishell

OBJ = $(SRC:.c=.o)

Libft = libft/libft.a

LIBFT_PATH = ./libft/

GREEN = "\033[1;32m"

YELLOW = "\033[1;33m"

URED = "\033[4;31m"

NO_COLOUR = "\033[0m"

INCLUDE = -I ./includes/ \
	-I ./libft/ \

READLINE = -lreadline

nb:=1

all: $(NAME)
	

MAKE = make --silent --jobs

	

.c.o :
	@$(CC) $(CFLAGS) $(INCLUDE) -c -g3 $< -o $(<:.c=.o)
	@echo -n $(YELLOW)
	@echo -n "\r[Compiling $(nb) / $(NO_OF_FILES) Minishell Objects]"
	$(eval nb=$(shell echo $$(($(nb)+1))))


$(NAME): $(OBJ)
	@echo -n $(GREEN)
	@echo "\n>>>>>>>>>>>>DONE<<<<<<<<<<< ✅\n"
	@echo -n $(URED)
	@echo -n "\n	COMPILING LIBFT\n"
	@echo -n $(NO_COLOUR)
	@make --silent -C libft
	@echo -n $(YELLOW)
	@$(CC) $(OBJ) $(READLINE)  $(Libft) $(CFLAGS) -o $(NAME) $(INCLUDE)
	@echo $(GREEN)	">>>>>>>>>>>MINISHELL READY 💪<<<<<<<<<<<<<<<<!"


clean:
	@rm -rf $(OBJ)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean


.PHONY: all re fclean clean

re: fclean all