/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiloub <shiloub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:41:42 by amontant          #+#    #+#             */
/*   Updated: 2022/05/27 16:07:44 by shiloub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*parse_env(char **env_t)
{
	int		i;
	t_env	*env;

	env = NULL;
	i = 0;
	while (env_t[i])
	{
		env_add_back(&env, env_new(get_name(env_t[i]), get_value(env_t[i])));
		i++;
	}
	return (env);
}

void	ft_export(t_env	**env, char **params)
{
	int	i;

	i = 1;
	if (params[i] == NULL)
		print_env(*env);
	else
	{
		while (params[i])
		{
			export_variable(env, params[i]);
			check_rm_double(env);
			i++;
		}
	}
	g_estatus = 0;
}

void	export_variable(t_env **env, char *new_v)
{
	char	*name;
	char	*value;

	if (!check_valid_variable(new_v))
		return ;
	name = get_name(new_v);
	value = get_value(new_v);
	env_add_back(env, env_new(name, value));
}
