/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:11:37 by clmurphy          #+#    #+#             */
/*   Updated: 2022/04/22 16:17:08 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char	**env)
{
	char		*str;
	t_mshell	*mshell;

	if (!check_args(ac, av))
		return (1);
	mshell = init_mshell(env);
	if (mshell == NULL)
		return (-1);
	str = NULL;
	while (1)
	{
		if (ft_read(str, mshell) == -1)
			break ;
		if (str)
			free (str);
	}
	return (0);
}

int	ft_read(char *str, t_mshell *mshell)
{
	str = readline("\033[1;33m  Shell  ✗ \033[0m");
	if (str)
	{
		add_history(str);
		parse_command(str, mshell);
		rl_redisplay();
		return (1);
	}
	else
	{
		printf("exit\n");
		free_mshell(mshell, str);
		return (-1);
	}
}

void	free_mshell(t_mshell *mshell, char *str)
{
	if (str)
		free (str);
	//free_command(&mshell->command);
	env_free(mshell->env);
 	if (mshell)
		free(mshell); 
}
	