/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiloub <shiloub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:02:54 by amontant          #+#    #+#             */
/*   Updated: 2022/04/27 16:01:23 by shiloub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	ft_exe(t_mshell *mini)
{
	t_command	*current;
	
	current = mini->command;
	while (current)
	{
		current->out = parse_redir_out(current->value);
		current->value = command_clear_all(current->value);
		current = current->next;
	}
	if (is_builtins(mini->command->value) && cmd_list_size(mini->command) == 1)
		exe_builtins(mini->command->value, &mini->env);
	else
		exec_cmd(mini->env, mini->command, mini->command);
}

void	exec_cmd(t_env *env, t_command *command, t_command *current)
{
	int			pid;
	int			*pipe_fd;
	int			i;
	
	pipe_fd = set_pipe(command);
	i = 0;
	
	while (current)
	{
		pid = fork();
		if (pid == 0)
		{
			exit_if_builtin_last(command, current);
		 	execute(env, command, current, pipe_fd, i);
		}
		else if (cmd_lst_pos(command, current) == cmd_list_size(command))
		{
			if (is_builtins(current->value))
				exe_builtins(current->value, &env);
		}
		i += 2;
		current = current->next;
	}
	close_pipe_n_wait(pipe_fd);
}
void	exit_if_builtin_last(t_command *command, t_command *current)
{
	if (cmd_lst_pos(command, current) == cmd_list_size(command))
	{
		if (is_builtins(current->value))
			exit(0);
	}
}
void	close_pipe_n_wait(int *pipe_fd)
{
	int	i;

	i = 0;
	while (pipe_fd[i])
		close(pipe_fd[i++]);
	while (waitpid(-1, 0, 0) != -1)
		i++;
}

void	execute(t_env *env, t_command *command, t_command *current, int *pipe_fd, int i)
{
	char	*path;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		free(pipe_fd);
		ft_putstr_fd("Command not found\n", 2);
		exit(0);
	}
	execve(path, current->value, env_to_tab(env));
	exit(0);
}

int	*set_pipe(t_command *command)
{
	int	*pipe_fd;
	int	i;

	i = 0;
	pipe_fd = malloc(sizeof(int) * cmd_list_size(command) * 2);
	while (i < (cmd_list_size(command) - 1))
	{
		pipe(pipe_fd + i * 2);
		i ++;
	}
	pipe_fd[i * 2] = 0;
	return (pipe_fd);
}

void	ft_dup(t_command *command, t_command *current, int *pipe_fd, int i)
{
	int	j;
	int	out_fd;

	j = 0;
	if (cmd_lst_pos(command, current) == 1 && cmd_list_size(command) > 1)
		dup2(pipe_fd[1], 1);
	else if (cmd_lst_pos(command, current) == cmd_list_size(command) &&\
	cmd_list_size(command) > 1)
	  	dup2(pipe_fd[i - 2], 0);
	else if (cmd_list_size(command) > 1)
	{
	 	dup2(pipe_fd[i - 2], 0);
	 	dup2(pipe_fd[i + 1], 1);
	}
	out_fd = make_redir_out(current);
	if (out_fd)
	 	dup2(out_fd, 1);
	while (pipe_fd[j])
		close(pipe_fd[j++]);
}

int	make_redir_out(t_command *command)
{
	int	fd;

	fd = 0;
	while (command->out)
	{
		fd = open(command->out->name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == 0)
			printf("erreur de creation de file out mais j'exite pas encore");
		command->out = command->out->next;
	}
	return (fd);
}
