/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiloub <shiloub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 19:14:45 by shiloub           #+#    #+#             */
/*   Updated: 2022/04/21 19:15:20 by shiloub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_builtins(char **params, t_env **env)
{
	if (!ft_strncmp(params[0], "pwd", 5))
		pwd();
	if (!ft_strncmp(params[0], "cd", 5))
		cd(params);
	if (!ft_strncmp(params[0], "echo", 5))
		echo(params);
	if (!ft_strncmp(params[0], "export", 7))
		ft_export(env, params);
	if (!ft_strncmp(params[0], "unset", 7))
		ft_unset(env, params);
	if (!ft_strncmp(params[0], "exit", 5))
		exit(0);
	if (!ft_strncmp(params[0], "env", 5))
	{
		print_env(*env);
	}
}

int	is_builtins(char **params)
{
	if (!ft_strncmp(params[0], "pwd", 5))
		return (1);
	if (!ft_strncmp(params[0], "cd", 5))
		return (1);
	if (!ft_strncmp(params[0], "echo", 5))
		return (1);
	if (!ft_strncmp(params[0], "export", 7))
		return (1);
	if (!ft_strncmp(params[0], "unset", 7))
		return (1);
	if (!ft_strncmp(params[0], "exit", 5))
		return (1);
	if (!ft_strncmp(params[0], "env", 5))
		return (1);
	return (0);
}

char	**env_to_tab(t_env *env)
{
	t_env	*current;
	char	**env_tab;
	int		i;

	current = env;
	env_tab = malloc(sizeof(char *) * (lst_env_size(env) + 1));
	i = 0;
	while (current)
	{
		env_tab[i++] = ft_strjoin_f(ft_strjoin(current->name, "="), current->value);
		current = current->next;
	}
	env_tab[i] = NULL;
	return (env_tab);
}

int	lst_env_size(t_env *env)
{
	int		i;
	t_env	*current;

	current = env;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}
