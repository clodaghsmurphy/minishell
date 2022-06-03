/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:26:06 by clmurphy          #+#    #+#             */
/*   Updated: 2022/06/03 15:09:45 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_estatus;

t_mshell	*init_mshell(char **env)
{
	t_mshell	*mshell;

	armsignals();
	mshell = ft_calloc(sizeof(t_mshell), 1);
	if (!mshell)
		return (NULL);
	mshell->s_error = 0;
	mshell->env = parse_env(env);
	mshell->pids = NULL;
	return (mshell);
}

void	syntax_error(t_mshell *mshell)
{
	if (mshell->s_error != 1)
		printf("\033[1m\033[31m  Syntax Error RIP\n");
	mshell->s_error = 1;
	g_estatus = 2;
}

int	init_values(int	*i, int *size, t_command **temp_command, \
				t_phrase **temp_phrase)
{
	*i = 0;
	*size = phrase_lstsize(*temp_phrase);
	(*temp_command)->value = (char **)malloc(sizeof(char *) * (*size + 1));
	if (!(*temp_command))
		return (-1);
	return (0);
}
