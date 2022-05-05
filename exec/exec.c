/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiloub <shiloub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:02:54 by amontant          #+#    #+#             */
/*   Updated: 2022/05/04 15:26:29 by shiloub          ###   ########.fr       */
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
		current->in = parse_redir_in(current->value);
		current->value = command_clear_all_out(current->value);
		current->value = command_clear_all_in(current->value);
		current = current->next;
	}
	mini->pipe_fd = NULL;
	//error("random", mini);
	exec_cmd(mini);
	free(mini->pipe_fd);
	free_command(&mini->command);
	//env_free(mini->env);
	//free(mini);
}

void	exec_cmd(t_mshell *mini)
{
	int			pid;
	int			i;
	t_command	*current;
	
	mini->pipe_fd = set_pipe(mini->command);
	 i = 0;
	current = mini->command;
	while (current)
	{
		pid = fork();
		if (pid == 0)
		{
			exit_if_builtin_last(mini, current);
		 	execute(mini, current, i);
		}
		else if (cmd_lst_pos(mini->command, current) == cmd_list_size(mini->command))
		{
			if (is_builtins(current->value))
				execute(mini, current, i);
		}
		i += 2;
		current = current->next;
	}
	close_pipe_n_wait(mini->pipe_fd);
}

void	execute(t_mshell *mini, t_command *current, int i)
{
	char	*path;
	ft_dup(mini, current, i);
	if (is_builtins(current->value))
	{
		exe_builtins(current->value, &mini->env);
		exit(0);
	}
	path = find_path(mini->env, current->value);
	if (path == NULL)
	{
		ft_putstr_fd(current->value[0], 2);
		error(" ", mini);
	}
	execve(path, current->value, env_to_tab(mini->env));
	exit(0);
}

void	ft_dup(t_mshell *mini, t_command *current, int i)
{
	int	j;
	int	out_fd;
	int	in_fd;

	j = 0;
	if (cmd_lst_pos(mini->command, current) == 1 && cmd_list_size(mini->command) > 1)
		dup2(mini->pipe_fd[1], 1);
	else if (cmd_lst_pos(mini->command, current) == cmd_list_size(mini->command) &&\
	cmd_list_size(mini->command) > 1)
	  	dup2(mini->pipe_fd[i - 2], 0);
	else if (cmd_list_size(mini->command) > 1)
	{
	 	dup2(mini->pipe_fd[i - 2], 0);
	 	dup2(mini->pipe_fd[i + 1], 1);
	}
	out_fd = make_redir_out(current, mini);
	in_fd = make_redir_in(current, mini);
	if (out_fd)
	 	dup2(out_fd, 1);
	if (in_fd)
	  	dup2(in_fd, 0);
	while (mini->pipe_fd[j])
		close(mini->pipe_fd[j++]);
}

int	make_redir_out(t_command *command, t_mshell *mini)
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
			error(command->out->name, mini);
		if (command->out->next)
			close(fd);
		command->out = command->out->next;
	}
	return (fd);
}

int	make_redir_in(t_command *command, t_mshell *mini)
{
	int	fd;

	fd = 0;
	while (command->in)
	{
		// if (command->out->in == 1)
		// 	fd = open(command->out->name, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (command->in->type == 0)
			fd = open(command->in->name, O_RDONLY);
		if (fd < 0)
			error(command->in->name, mini);
		command->in = command->in->next;
	}
	return (fd);
}

void	error(char *str, t_mshell *mini)
{
	perror(str);
	free(mini->pipe_fd);
	free_command(&mini->command);
	env_free(mini->env);
	free(mini);
	exit(EXIT_FAILURE);
}