/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:33:36 by amontant          #+#    #+#             */
/*   Updated: 2022/04/13 13:36:38 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "../libft/libft.h"

# define KEY_UP 38

struct	s_command;
struct	s_mshell;

typedef struct s_command
{
	char				**value;
	struct s_command	*next;
}	t_command;

typedef enum e_token
{
	string = 0,
	builtin = 1,
	flag = 2,
	PIPE = 3,
	redir_in = 4,
	redir_out = 5,
	d_variable = 6,
	here_doc = 7,
	here_doc_del = 8,
	redir_app = 9,
}	t_token;

typedef struct s_split
{
	char				c;
	struct s_split		*next;
}	t_split;

typedef struct s_phrase
{
	char				*str;
	int					token;
	struct s_phrase		*next;
}	t_phrase;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}	t_env;

typedef struct s_mshell
{
	t_env		*env;
	char		**path;
	t_command	*command;
	t_phrase	*phrase;
	t_split		*word;
}	t_mshell;

/**************MAIN*****************/
int			ft_read(char *str, t_mshell *mshell);
void		free_mshell(t_mshell *mshell, char *str);

/**************PARSE****************/
int			check_args(int ac, char **av);
int			parse_command(char *str, t_mshell *mshell);
void		create_command(t_mshell *mshell);

/***********SPLIT*******************/
void		split_command(char *str, t_mshell *mshell);
void		make_word(t_split **word, t_mshell *mshell);
void		parse_quotes(t_split **word, t_mshell *mshell, char *str, int *i);
int			parse_string(t_split **word, t_mshell *mshell, char *str, int *i);
void		parse_delimiter(t_split **word, t_mshell *mshell, \
			char *str, int *i);

/***********SPLIT_UTILS*******************/
t_split		*split_lstnew(char c);
void		split_lstadd_back(t_split **alst, t_split *new);
int			split_lstsize(t_split *lst);
void		phrase_lstadd_back(t_phrase **alst, t_phrase *new);
void		print_split(t_split **split);

/***********WORD_UTILS*******************/
void		print_phrase(t_phrase **phrase);
void		ft_wordclear(t_split **lst);
t_phrase	*phrase_lstnew(char *str);
int			phrase_lstsize(t_phrase *lst);

/************COMMAND_UTILS**********/
void		command_lstadd_back(t_command **alst, t_command *new);
t_command	*command_lstnew(char **commands);
void		print_tab(char **tab);
int			count_delim(t_phrase **phrase);
void		freetab(char **tab);
void		print_command(t_mshell *mshell);

/**************INIT*****************/
int			init_mshell(t_mshell *mshell);

/**************ARM_SIGNAL************/
void		armsignals(void);
void		sig_handler(int signum);

/************ASSIGN_TOKENS***********/
void		assign_tokens(t_mshell *mshell);
int			is_variable(char *str);
int			is_builtin(char *str);

#endif