/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiloub <shiloub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:56:46 by amontant          #+#    #+#             */
/*   Updated: 2022/06/07 23:01:57 by shiloub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_env	**env, char **params)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (params[i] == NULL)
		;
	else
	{
		while (params[i])
		{
			if (!valid_param(params[i]))
			{
				ft_putstr_fd("export: ", 2);
				ft_putstr_fd(params[i], 2);
				ft_putstr_fd(" : not a valid identifier\n", 2);
				status = 1;
			}
			else
				unset_variable(env, params[i]);
			i++;
		}
	}
	g_estatus = status;
}

int	valid_param(char *param)
{
	int	i;

	i = 0;
	while (param[i])
	{
		if (!is_alpha_num(param[i]))
			return (0);
		i++;
	}
	return (1);
}

int	simul_ft_unset(char **params)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (params[i] == NULL)
		;
	else
	{
		while (params[i])
		{
			if (!valid_param(params[i]))
				status = 1;
			i++;
		}
	}
	return (status);
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
