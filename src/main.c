/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:11:37 by clmurphy          #+#    #+#             */
/*   Updated: 2022/06/03 17:45:55 by clmurphy         ###   ########.fr       */
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
	armsignals();
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
	str = readline("\001\033[1;48;2;50;157;168m\002  Shell \001✗\002 \001\033[0m\002");
	if (str)
	{
		add_history(str);
		mshell->s_error = 0;
		mshell->hdoc_flag = 0;
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
	env_free(mshell->env);
	free_phrase(&mshell->phrase);
	if (mshell)
		free(mshell);
}

void	free_command(t_command **command)
{
	t_command	*temp;
	t_command	*current;

	if (command == NULL)
		return ;
	current = *command;
	while (current != NULL)
	{
		free_tab(current->value);
		free_redir_in(current->in);
		free_redir_out(current->out);
		temp = current;
		current = current->next;
		free(temp);
	}
}
