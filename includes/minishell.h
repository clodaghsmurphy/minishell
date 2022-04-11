/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:06:00 by clmurphy          #+#    #+#             */
/*   Updated: 2022/04/11 16:15:30 by amontant         ###   ########.fr       */
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
	char				**commands;
	struct s_command	*next;
}	t_command;

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
}	t_mshell;

/**************PARSE****************/
int			check_args(int ac, char **av);
int			parse_command(char *str, t_mshell *mshell);
/************COMMAND_UTILS**********/
void		command_lstadd_back(t_command **alst, t_command *new);
t_command	*command_lstnew(char **commands);
/**************INIT*****************/
int			init_mshell(t_mshell *mshell);

#endif