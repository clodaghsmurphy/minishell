/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:25:03 by shiloub           #+#    #+#             */
/*   Updated: 2022/06/07 19:47:43 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_if_builtin_only(t_mshell *mini, t_command *current)
{
	if (cmd_lst_pos(mini->command, current) == cmd_list_size(mini->command) \
	&& cmd_list_size(mini->command) == 1)
	{
		if (is_builtins(current->value))
		{
			free(mini->pipe_fd);
			free_command(&mini->command);
			free(mini->pids);
			env_free(mini->env);
			free(mini);
			exit(0);
		}
	}
}

void	close_pipe_n_wait(int *pipe_fd, int *pids)
{
	int	i;

	i = 0;
	while (pipe_fd[i])
		close(pipe_fd[i++]);
	i = 0;
	while (pids[i])
	{
		waitpid(pids[i], &g_estatus, 0);
		if (WIFEXITED(g_estatus))
			g_estatus = WEXITSTATUS(g_estatus);
		else if (WIFSIGNALED(g_estatus))
			g_estatus = 130;
		i++;
	}
	free(pids);
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

void	get_last_retour_builtin(t_command *lst, t_mshell *mini)
{
	t_command	*current;
	int			value;

	value = -1;
	current = lst;
	if (!current)
		return ;
	while (current->next)
		current = current->next;
	if (is_builtins(current->value))
		value = simul_exe_builtins(current->value, mini);
	if (value != -1)
		g_estatus = value;
}
