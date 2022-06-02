/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiloub <shiloub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:02:54 by amontant          #+#    #+#             */
/*   Updated: 2022/06/01 17:22:04 by shiloub          ###   ########.fr       */
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
	if (!signal_hd)
		exec_cmd(mini);
	else
		ft_putstr_fd("\n", 1);
	delete_hd(mini->command);
	free(mini->pipe_fd);
	free_command(&mini->command);
	armsignals();
}
void	delete_hd(t_command *command)
{
	t_command *current;
	t_redir_in *cur;

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
void	test(t_mshell *mini, t_command *current, int i, int pid);

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
		test(mini, current, i, pid);
		i += 2;
		j ++;
		current = current->next;
	}
	close_pipe_n_wait(mini->pipe_fd, mini->pids);
	get_last_retour_builtin(mini->command, mini);
	mini->pids = NULL;
}


void	test(t_mshell *mini, t_command *current, int i, int pid)
{
	int			save_in;
	int			save_out;

	if (pid == 0)
	{
		signal_def();
		exit_if_builtin_only(mini, current);
		execute(mini, current, i);
	}
	else if (cmd_lst_pos(mini->command, current) == cmd_list_size(mini->command))
	{
		if (is_builtins(current->value) && cmd_list_size(mini->command) == 1)
		{
			save_in = dup(0);
			save_out = dup(1);
			execute(mini, current, i);
			dup2(save_in, 0);
			dup2(save_out, 1);
		}
	}
}
void	get_last_retour_builtin(t_command *lst, t_mshell *mini)
{
	t_command	*current;
	int			value;

	value = -1;
	current = lst;
	while (current->next)
		current = current->next;
	if (is_builtins(current->value))
		value = simul_exe_builtins(current->value, mini);
	if (value != -1)
		g_estatus = value;
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

void	ft_dup(t_mshell *mini, t_command *current, int i)
{
	int	j;
	int	out_fd;
	int	in_fd;

	j = 0;
	if (cmd_lst_pos(mini->command, current) == 1 && cmd_list_size(mini->command) > 1)
		dup2(mini->pipe_fd[1], 1);
	else if (cmd_lst_pos(mini->command, current) == cmd_list_size(mini->command) &&\
	cmd_list_size(mini->command) > 1 && !is_builtins(current->value))
	  	dup2(mini->pipe_fd[i - 2], 0);
	else if (cmd_list_size(mini->command) > 1)
	{
		if (!is_builtins(current->value))
	 		dup2(mini->pipe_fd[i - 2], 0);
	 	dup2(mini->pipe_fd[i + 1], 1);
	}
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
	while (mini->pipe_fd[j])
		close(mini->pipe_fd[j++]);
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