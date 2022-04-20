/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiloub <shiloub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:02:54 by amontant          #+#    #+#             */
/*   Updated: 2022/04/20 16:44:45 by shiloub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	ft_exe(t_mshell *mini)
{
	int	pid;

	if (is_builtins(mini->command->value) && cmd_list_size(mini->command) == 1)
		exe_builtins(mini->command->value, &mini->env);
	else
	{
		exec_cmd(mini->env, mini->command, mini->command);
	}
}

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

void	exec_cmd(t_env *env, t_command *command, t_command *current)
{
	char	*path;
	int		pid;
	int		*pipe_fd;
	int		i = 0;
	
	pipe_fd = malloc(sizeof(int) * cmd_list_size(command) * 2);
	while (i < (cmd_list_size(command) - 1))
	{
		pipe(pipe_fd + i * 2);
		i ++;
	}
	pipe_fd[i * 2] = 0;
	i = 0;
	wait(0);
	while (current)
	{
		pid = fork();
		if (pid == 0)
		{
			ft_dup(command, current, pipe_fd, i);
			if (is_builtins(current->value))
			{
				exe_builtins(current->value, &env);
				exit(0);
			}
			path = find_path(env, current->value);
			execve(path, current->value, env_to_tab(env));
			exit(0);
		}
		i += 2;
		current = current->next;
	}
	i = 0;
	while (pipe_fd[i])
		close(pipe_fd[i++]);
	while (waitpid(-1, 0, 0) != -1)
		i++;
}

void	ft_dup(t_command *command, t_command *current, int *pipe_fd, int i)
{
	int	j;
	j = 0;
	if (cmd_lst_pos(command, current) == 1 && cmd_list_size(command) > 1)
		dup2(pipe_fd[1], 1);
	else if (cmd_lst_pos(command, current) == cmd_list_size(command))
	  	dup2(pipe_fd[i - 2], 0);
	else
	{
	 	dup2(pipe_fd[i - 2], 0);
	 	dup2(pipe_fd[i + 1], 1);
	}
	while (pipe_fd[j])
		close(pipe_fd[j++]);
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

