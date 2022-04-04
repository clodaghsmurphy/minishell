/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:06:00 by clmurphy          #+#    #+#             */
/*   Updated: 2022/04/04 18:49:18 by clmurphy         ###   ########.fr       */
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
# include "libft.h"

struct	s_command;
struct	s_mshell;

typedef struct s_command
{
	char				**commands;
	struct s_command	*next;
}	t_command;

typedef struct s_mshell
{
	char		**env;
	char		**path;
	t_command	*command;
}	t_mshell;

/**************PARSE****************/
int	check_args(int ac, char **av);
int	parse_command(char *str, t_mshell *mshell);
/**************INIT*****************/
int	init_mshell(t_mshell *mshell);

#endif