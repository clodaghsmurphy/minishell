/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:24:03 by amontant          #+#    #+#             */
/*   Updated: 2022/03/21 18:32:46 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_path_fd_1(t_process *process, char *infile_name)
{
	int	error_;

	error_ = 0;
	if (process->path_1 == NULL)
		error_ = 1;
	if (process->infile_fd == -1)
	{
		free_process(process);
		error(infile_name);
	}
	if (error_ == 1)
	{
		free_process(process);
		error("command 1");
	}
}

void	free_to_exit(char **paths, t_process *p)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	free_process(p);
	write(1, "Command empty\n", 14);
	exit(0);
}

void	error_path_fd_2(t_process *process, char *outfile_name)
{
	int	error_;

	error_ = 0;
	if (process->path_2 == NULL)
		error_ = 1;
	if (process->outfile_fd == -1)
	{
		free_process(process);
		error(outfile_name);
	}
	if (error_ == 1)
	{
		free_process(process);
		error("command 2");
	}
}

void	error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	free_process(t_process *process)
{
	free_tab(process->cmd_params_1);
	free_tab(process->cmd_params_2);
	free(process->path_1);
	free(process->path_2);
	free(process);
}
