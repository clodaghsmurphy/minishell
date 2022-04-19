/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:02:54 by amontant          #+#    #+#             */
/*   Updated: 2022/04/19 21:34:48 by amontant         ###   ########.fr       */
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
		//pid = fork();
		//if (pid == 0)
		//{
			exec_cmd(mini->env, mini->command, mini->command);
		//}
		//waitpid(pid, 0, 0);
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
	int		tab_pid[100];

	int i = 0;
	while (i < 100)
		tab_pid[i++] = 0;
	i = 0;
	
	while (current)
	{
		if (current->next)
		{
			if (pipe(current->next->pipe_fd) == -1)
			exit(0);
		}
		pid = fork();
		if (pid != 0)
			tab_pid[i++] = pid;
		if (pid == 0)
		{
			ft_dup(command, current);
			if (is_builtins(current->value))
			{
				exe_builtins(current->value, &env);
				exit(0);
			}
			path = find_path(env, current->value);
			execve(path, current->value, env_to_tab(env));
			exit(0);
		}
		current = current->next;
	}
	i = 0;
	while (tab_pid[i] != 0)
	{
		printf("j'attend pid %d et je suis pid %d\n", tab_pid[i], pid);		
		waitpid(tab_pid[i++], 0, 0);
		printf("c bon !\n");
	}
}

void	ft_dup(t_command *command, t_command *current)
{
	if (cmd_lst_pos(command, current) == 1 && cmd_list_size(command) > 1)
	{
		close(current->next->pipe_fd[0]);
		dup2(current->next->pipe_fd[1], 1);
	}
	else if (cmd_lst_pos(command, current) == cmd_list_size(command))
	{
		close(current->pipe_fd[1]);
	 	dup2(current->pipe_fd[0], 0);
	}
	else
	{
		close(current->next->pipe_fd[0]);
		close(current->pipe_fd[1]);
		dup2(current->pipe_fd[0], 0);
		dup2(current->next->pipe_fd[1], 1);
	}
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

