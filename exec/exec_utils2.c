/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:25:03 by shiloub           #+#    #+#             */
/*   Updated: 2022/05/05 17:25:54 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_if_builtin_only(t_mshell *mini, t_command *current)
{
	if (cmd_lst_pos(mini->command, current) == cmd_list_size(mini->command)
	&& cmd_list_size(mini->command) == 1)
	{
		if (is_builtins(current->value))
		{
			free(mini->pipe_fd);
			free_command(&mini->command);
			env_free(mini->env);
			free(mini);
			exit(0);
		}
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
