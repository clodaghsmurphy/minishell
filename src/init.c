/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:26:06 by clmurphy          #+#    #+#             */
/*   Updated: 2022/05/24 16:50:57 by clmurphy         ###   ########.fr       */
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
	mshell->q_error = 0;
	mshell->s_error = 0;
	mshell->env = parse_env(env);
	return (mshell);
}

void	syntax_error(t_mshell *mshell)
{
	if (mshell->s_error != 1)
		printf("\033[1m\033[31m  Syntax Error RIP\n");
	mshell->s_error = 1;
	g_estatus = 2;
}
