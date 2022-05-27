/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiloub <shiloub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:56:46 by amontant          #+#    #+#             */
/*   Updated: 2022/05/27 15:56:44 by shiloub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_one(t_env **lst, t_env *to_del);
void	unset_variable(t_env **env, char *variable_name);

void	ft_unset(t_env	**env, char **params)
{
	int	i;

	i = 1;
	if (params[i] == NULL)
		;
	else
	{
		while (params[i])
		{
			unset_variable(env, params[i]);
			i++;
		}
	}
	g_estatus = 0;
}

void	unset_variable(t_env **env, char *variable_name)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (!ft_strncmp(current->name, variable_name, 2147483647))
		{
			del_one(env, current);
			return ;
		}
		current = current->next;
	}
}
