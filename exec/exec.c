/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:02:54 by amontant          #+#    #+#             */
/*   Updated: 2022/06/07 19:47:00 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exe(t_mshell *mini)
{
	t_command	*current;
	int			signal_hd;

	current = mini->command;
	while (current)
	{
		current->out = parse_redir_out(current->value);
		current->in = parse_redir_in(current->value);
		current->value = command_clear_all_out(current->value);
		current->value = command_clear_all_in(current->value);
		find_replace_hd(current->in);
		current = current->next;
	}
	mini->pipe_fd = NULL;
	signal_hd = launch_hd(mini);
	if (exit_if_pas_de_commande(mini))
		return ;
	g_estatus = 130;
	if (!signal_hd)
		exec_cmd(mini);
	else
		ft_putstr_fd("\n", 1);
	end_fonction(mini);
}

void	delete_hd(t_command *command)
{
	t_command	*current;
	t_redir_in	*cur;

	current = command;
	while (current)
	{
		cur = current->in;
		while (cur)
		{
			if (cur->stop)
				unlink(cur->name);
			cur = cur->next;
		}
		current = current->next;
	}
}

void	exec_cmd(t_mshell *mini)
{
	int			pid;
	int			i;
	int			j;
	t_command	*current;

	mini->pids = malloc(sizeof(int) * (cmd_list_size(mini->command) + 1));
	mini->pids[cmd_list_size(mini->command)] = 0;
	mini->pipe_fd = set_pipe(mini->command);
	i = 0;
	j = 0;
	current = mini->command;
	while (current)
	{
		end_signals();
		pid = fork();
		if (pid > 0)
			mini->pids[j] = pid;
		exe_child_daron(mini, current, i, pid);
		i += 2;
		j ++;
		current = current->next;
	}
	close_pipe_n_wait(mini->pipe_fd, mini->pids);
	get_last_retour_builtin(mini->command, mini);
	mini->pids = NULL;
}

void	exe_child_daron(t_mshell *mini, t_command *cur, int i, int pid)
{
	int			save_in;
	int			save_out;

	if (pid == 0)
	{
		signal_def();
		exit_if_builtin_only(mini, cur);
		execute(mini, cur, i);
	}
	else if (cmd_lst_pos(mini->command, cur) == cmd_list_size(mini->command))
	{
		if (is_builtins(cur->value) && cmd_list_size(mini->command) == 1)
		{
			save_in = dup(0);
			save_out = dup(1);
			execute(mini, cur, i);
			dup2(save_in, 0);
			dup2(save_out, 1);
			close(save_in);
			close(save_out);
		}
	}
}

void	execute(t_mshell *mini, t_command *current, int i)
{	
	char	*path;

	ft_dup(mini, current, i);
	if (is_builtins(current->value))
	{
		exe_builtins(current->value, &mini->env, mini);
		if (cmd_list_size(mini->command) != 1)
		{
			free_mini(mini);
			exit(0);
		}
		else
			return ;
	}
	path = find_path(mini->env, current->value);
	if (path == NULL)
	{
		ft_putstr_fd(current->value[0], 2);
		error(" ", mini, 127);
	}
	execve(path, current->value, env_to_tab(mini->env));
	exit(0);
}
