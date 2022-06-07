/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_redir_in_out.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 22:56:41 by shiloub           #+#    #+#             */
/*   Updated: 2022/06/04 12:24:04 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup(t_mshell *mini, t_command *current, int i)
{
	int	j;

	j = 0;
	if (cmd_lst_pos(mini->command, current) == 1 && \
	cmd_list_size(mini->command) > 1)
		dup2(mini->pipe_fd[1], 1);
	else if (cmd_lst_pos(mini->command, current) == \
	cmd_list_size(mini->command) && \
	cmd_list_size(mini->command) > 1)
	{
		dup2(mini->pipe_fd[i - 2], 0);
	}
	else if (cmd_list_size(mini->command) > 1)
	{
		dup2(mini->pipe_fd[i - 2], 0);
		dup2(mini->pipe_fd[i + 1], 1);
	}
	dup_redir_in_out(current, mini);
	while (mini->pipe_fd[j])
		close(mini->pipe_fd[j++]);
}

void	dup_redir_in_out(t_command *current, t_mshell *mini)
{
	int	in_fd;
	int	out_fd;

	out_fd = make_redir_out(current, mini);
	in_fd = make_redir_in(current, mini);
	if (out_fd)
	{
		dup2(out_fd, 1);
		close(out_fd);
	}
	if (in_fd)
	{
		dup2(in_fd, 0);
		close(in_fd);
	}
}

int	make_redir_out(t_command *command, t_mshell *mini)
{
	int			fd;
	t_redir_out	*current;

	fd = 0;
	current = command->out;
	while (current)
	{
		if (current->append == 1)
			fd = open(current->name, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else if (current->append == 0)
			fd = open(current->name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd < 0)
			error(current->name, mini, 1);
		if (current->next)
			close(fd);
		current = current->next;
	}
	return (fd);
}

int	make_redir_in(t_command *command, t_mshell *mini)
{
	t_redir_in	*current;
	int			fd;

	fd = 0;
	current = command->in;
	while (current)
	{
		if (current->type == 0)
			fd = open(current->name, O_RDONLY);
		if (fd < 0)
			error(current->name, mini, 1);
		if (current->next)
			close(fd);
		current = current->next;
	}
	return (fd);
}

void	error(char *str, t_mshell *mini, int erreur)
{
	perror(str);
	free_mini(mini);
	exit(erreur);
}
