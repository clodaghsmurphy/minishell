/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:06:52 by amontant          #+#    #+#             */
/*   Updated: 2022/03/21 19:01:34 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd_1(char **av, char **env, t_process *process)
{
	int		infile_fd;
	int		temp_fd;
	int		pid;

	if (pipe(process->pipe_fd) == -1)
		error("PROCESS CAN'T PIPE");
	pid = fork();
	if (pid == 0)
		exec_cmd_2(av, env, process);
	else
	{
		close(process->pipe_fd[0]);
		infile_fd = open(av[1], O_RDONLY);
		temp_fd = infile_fd;
		process->infile_fd = infile_fd;
		if (infile_fd == -1 || process->path_1 == NULL)
			error_path_fd_1(process, av[1]);
		dup2(infile_fd, 0);
		dup2(process->pipe_fd[1], 1);
		execve(process->path_1, process->cmd_params_1, env);
		free_process(process);
		close(temp_fd);
		error("ERROR EXECVE\n");
	}
}

void	exec_cmd_2(char **av, char **env, t_process *process)
{
	int		outfile_fd;
	int		temp_fd;

	close(process->pipe_fd[1]);
	outfile_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	process->outfile_fd = outfile_fd;
	temp_fd = outfile_fd;
	if (outfile_fd == -1 || process->path_2 == NULL)
		error_path_fd_2(process, av[4]);
	dup2(outfile_fd, 1);
	dup2(process->pipe_fd[0], 0);
	if (execve(process->path_2, process->cmd_params_2, env) == -1)
	{
		free_process(process);
		close(temp_fd);
		error("ERROR EXECVE\n");
	}
}

t_process	*set_process(char **av, char **env)
{
	t_process	*process;

	process = malloc(sizeof(t_process));
	init_process(process);
	process->path_1 = find_path(av[2], env, &process->cmd_params_1, process);
	process->path_2 = find_path(av[3], env, &process->cmd_params_2, process);
	return (process);
}

void	init_process(t_process *process)
{
	process->cmd_params_1 = NULL;
	process->cmd_params_2 = NULL;
	process->path_1 = NULL;
	process->path_2 = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_process	*process;
	int			pid;

	if (ac != 5 || env[0] == NULL)
	{
		error("BAD ARGUMENTS OR ENV NULL\n");
		return (0);
	}
	process = set_process(av, env);
	pid = fork();
	if (pid == -1)
		error("PROCESS CAN'T FORK\n");
	if (pid == 0)
		exec_cmd_1(av, env, process);
	wait(0);
	free_process(process);
	return (0);
}
