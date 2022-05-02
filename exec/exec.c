/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiloub <shiloub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:02:54 by amontant          #+#    #+#             */
/*   Updated: 2022/04/29 15:51:57 by shiloub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	error(char *str);


void	ft_exe(t_mshell *mini)
{
	t_command	*current;
	
	current = mini->command;
	while (current)
	{
		current->out = parse_redir_out(current->value);
		current->in = parse_redir_in(current->value);
		current->value = command_clear_all_out(current->value);
		current->value = command_clear_all_in(current->value);
		current = current->next;
	}
	exec_cmd(mini);
}

void	exec_cmd(t_mshell *mini)
{
	int			pid;
	int			*pipe_fd;
	int			i;
	t_command	*current;
	
	pipe_fd = set_pipe(mini->command);
	i = 0;
	current = mini->command;
	while (current)
	{
		pid = fork();
		if (pid == 0)
		{
			exit_if_builtin_last(mini->command, current);
		 	execute(mini, current, pipe_fd, i);
		}
		else if (cmd_lst_pos(mini->command, current) == cmd_list_size(mini->command))
		{
			if (is_builtins(current->value))
				exe_builtins(current->value, &mini->env);
		}
		i += 2;
		current = current->next;
	}
	close_pipe_n_wait(pipe_fd);
}

void	execute(t_mshell *mini, t_command *current, int *pipe_fd, int i)
{
	char	*path;
	ft_dup(mini->command, current, pipe_fd, i);
	if (is_builtins(current->value))
	{
		exe_builtins(current->value, &mini->env);
		exit(0);
	}
	path = find_path(mini->env, current->value);
	if (path == NULL)
	{
		free(pipe_fd);
		ft_putstr_fd("Command not found\n", 2);
		exit(0);
	}
	execve(path, current->value, env_to_tab(mini->env));
	exit(0);
}

void	ft_dup(t_command *command, t_command *current, int *pipe_fd, int i)
{
	int	j;
	int	out_fd;
	int	in_fd;

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
	in_fd = make_redir_in(current);
	if (out_fd)
	 	dup2(out_fd, 1);
	if (in_fd)
	  	dup2(in_fd, 0);
	while (pipe_fd[j])
		close(pipe_fd[j++]);
}

int	make_redir_out(t_command *command)
{
	int	fd;

	fd = 0;
	while (command->out)
	{
		if (command->out->append == 1)
			fd = open(command->out->name, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else if (command->out->append == 0)
			fd = open(command->out->name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd < 0)
			error(command->out->name);
		if (command->out->next)
			close(fd);
		command->out = command->out->next;
	}
	return (fd);
}

int	make_redir_in(t_command *command)
{
	int	fd;

	fd = 0;
	while (command->in)
	{
		// if (command->out->in == 1)
		// 	fd = open(command->out->name, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (command->in->type == 0)
			fd = open(command->in->name, O_RDONLY);
		if (fd == 0)
			printf("erreur d'ouverture de file in mais j'exit pas encore");
		command->in = command->in->next;
	}
	return (fd);
}

void	error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}