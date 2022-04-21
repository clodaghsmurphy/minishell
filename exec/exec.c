/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiloub <shiloub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:02:54 by amontant          #+#    #+#             */
/*   Updated: 2022/04/15 12:03:07 by shiloub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_exe(t_mshell *mini)
{
	if (is_builtins(mini->command->value))
		exe_builtins(mini->command->value, &mini->env);
	else
		exec_cmd_1(mini->env, mini->command->value);
}

void exe_builtins(char **params, t_env **env)
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

int is_builtins(char **params)
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

void exec_cmd_1(t_env *env, char **cmd_params)
{
	char *path;
	int pid;

	pid = fork();
	if (pid == 0)
	{
		path = find_path(env, cmd_params);
		execve(path, cmd_params, env_to_tab(env));
	}
	wait(NULL);
}

char **env_to_tab(t_env *env)
{
	t_env *current;
	char **env_tab;
	int i;

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

int lst_env_size(t_env *env)
{
	int i;
	t_env *current;

	current = env;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}
