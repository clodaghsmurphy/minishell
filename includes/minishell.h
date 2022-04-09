/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:06:00 by clmurphy          #+#    #+#             */
/*   Updated: 2022/04/09 19:22:02 by clmurphy         ###   ########.fr       */
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

struct	s_command;
struct	s_mshell;

typedef struct s_command
{
	char				**value;
	struct s_command	*next;
}	t_command;

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
}	t_mshell;

/**************PARSE****************/
int			check_args(int ac, char **av);
int			parse_command(char *str, t_mshell *mshell);

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

/************COMMAND_UTILS**********/
void		command_lstadd_back(t_command **alst, t_command *new);
t_command	*command_lstnew(char **commands);

/**************INIT*****************/
int			init_mshell(t_mshell *mshell);

#endif