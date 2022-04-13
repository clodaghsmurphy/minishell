/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:26:06 by clmurphy          #+#    #+#             */
/*   Updated: 2022/04/13 16:29:19 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell	*init_mshell(char **env)
{
	t_mshell	*mshell;

	armsignals();
	mshell = ft_calloc(sizeof(t_mshell), 1);
	if (!mshell)
		return (NULL);
	mshell->env = parse_env(env);
	mshell->command = ft_calloc(sizeof(t_command), 1);
	if (!mshell->command)
		return (NULL);
	mshell->command = NULL;
	return (mshell);
}
