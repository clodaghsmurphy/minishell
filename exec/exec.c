/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiloub <shiloub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:02:54 by amontant          #+#    #+#             */
/*   Updated: 2022/04/17 20:15:40 by shiloub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	ft_exe(t_mshell *mini)
{
	if (is_builtins(mini->command->value) && cmd_list_size(mini->command) == 1)
		exe_builtins(mini->command->value, &mini->env);
	else
		exec_cmd(mini->env, mini->command, mini->command);
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
		return(1);
	if (!ft_strncmp(params[0], "cd", 5))
		return(1);
	if (!ft_strncmp(params[0], "echo", 5))
		return(1);
	if (!ft_strncmp(params[0], "export", 7))
		return(1);
	if (!ft_strncmp(params[0], "unset", 7))
		return(1);
	if (!ft_strncmp(params[0], "exit", 5))
		return(1);
	if (!ft_strncmp(params[0], "env", 5))
		return(1);
	return (0);
}

// void	exec_cmd(t_env *env, t_command *command, t_command *current)
// {
// 	char	*path;
// 	int		pid;
// 	int		pipe_fd[2];
	
// 	if (pipe(pipe_fd) == -1)
// 		exit(0);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		ft_dup(pipe_fd, command, current);
// 		if (is_builtins(current->value))
// 		{
// 			exe_builtins(current->value, &env);
// 			exit(0);
// 		}
// 		path = find_path(env, current->value);
// 		execve(path, current->value, env_to_tab(env));
// 	}
// 	else if (current->next)
// 		exec_cmd(env, command, current->next);
// 	//wait();
// }
void	exec_cmd(t_env *env, t_command *command, t_command *current)
{
	char	*path;
	int		pid;
	int		pipe_fd[2];
	char *str = malloc(1000);
	int i;
	i = 0;
	
	if (pipe(pipe_fd) == -1)
		exit(0);
	while (i < 2)
	{
		pid = fork();
		wait(0);
		if (pid == 0)
		{
			ft_dup(pipe_fd, command, current);
			if (is_builtins(current->value))
			{
				exe_builtins(current->value, &env);
				exit(0);
			}
			path = find_path(env, current->value);
			execve(path, current->value, env_to_tab(env));
			exit(0);
		}
		//wait();
		//else
		//{
		//	read(pipe_fd[0], str, 1000);
		//	printf("recu : %s\n", str);
		//}
		current = current->next;
		i ++;
		printf("i = %d", i);
	}
}

void	ft_dup(int pipe_fd[2], t_command *command, t_command *current)
{
	int	file_fd;
	char *str = malloc(10000);
	
	if (cmd_lst_pos(command, current) == 1 && cmd_list_size(command) > 1)
	{
		dup2(pipe_fd[1], 1);
		close(pipe_fd[0]);
	}
	else if (cmd_lst_pos(command, current) == 2)
	{
		file_fd = open("test.txt", O_RDONLY);
		//read(pipe_fd[0], str, 10000);
		//printf("recu ds dup :ffddfs  %s voila", str);
	 	//dup2(pipe_fd[0], 0);
	 	//dup2(file_fd, 0);
	 	//dup2(pipe_fd[0], 0);
	 	//dup2(file_fd, 0);
		
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

