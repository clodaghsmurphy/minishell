/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:17:23 by amontant          #+#    #+#             */
/*   Updated: 2022/06/04 12:20:53 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char **params)
{
	char	*error;

	if (!params[1])
	{
		ft_putstr_fd("cd : no argument\n", 2);
		return ;
	}
	if (params[2])
	{
		ft_putstr_fd("cd : too much arguments\n", 2);
		g_estatus = 1;
		return ;
	}
	error = ft_strjoin("cd: ", params[1]);
	if (chdir(params[1]) != 0)
		perror(error);
	free(error);
	g_estatus = 0;
}

int	simul_cd(char **params, t_mshell *mini)
{
	int		ret;
	int		pid;

	if (!params[1])
		return (1);
	if (params[2])
		return (1);
	pid = fork();
	if (pid == 0)
	{
		if (chdir(params[1]) != 0)
		{
			free_mini_simul_cd(mini);
			exit(1);
		}
		else
		{
			free_mini_simul_cd(mini);
			exit(0);
		}
	}
	waitpid(-1, &ret, 0);
	return (ret / 256);
}

void	free_mini_simul_cd(t_mshell *mini)
{
	free(mini->pipe_fd);
	mini->pipe_fd = NULL;
	free_command(&mini->command);
	mini->command = NULL;
	env_free(mini->env);
	mini->pids = NULL;
	free(mini);
}

void	pwd(void)
{
	char	wd[10000];

	getcwd(wd, 10000);
	ft_putstr_fd(wd, 1);
	ft_putchar_fd('\n', 1);
	g_estatus = 0;
}
