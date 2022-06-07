/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:41:42 by amontant          #+#    #+#             */
/*   Updated: 2022/06/07 19:42:20 by clmurphy         ###   ########.fr       */
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
	int	ret;

	i = 1;
	if (params[i] == NULL)
		print_env(*env);
	else
	{
		while (params[i])
		{
			ret = export_variable(env, params[i]);
			check_rm_double(env);
			i++;
		}
	}
}

int	simul_export_variable(t_env **env, char *new_v)
{
	(void)env;
	if (check_valid_variable(new_v) == 0)
		return (0);
	else if (check_valid_variable(new_v) == 2)
	{
		return (1);
	}
	return (0);
}

int	simul_ft_export(t_env **env, char **params)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (params[i] == NULL)
		return (0);
	else
	{
		while (params[i])
		{
			ret = simul_export_variable(env, params[i]);
			if (ret)
				return (1);
			i++;
		}
	}
	return (0);
}

int	export_variable(t_env **env, char *new_v)
{
	char	*name;
	char	*value;

	if (check_valid_variable(new_v) == 0)
		return (0);
	else if (check_valid_variable(new_v) == 2)
	{
		printf("export: %s : not a valid identifier\n", new_v);
		return (1);
	}
	name = get_name(new_v);
	value = get_value(new_v);
	env_add_back(env, env_new(name, value));
	return (0);
}
