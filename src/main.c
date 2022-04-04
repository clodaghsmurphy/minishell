/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:11:37 by clmurphy          #+#    #+#             */
/*   Updated: 2022/04/04 18:44:05 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*str;
	t_mshell	m_shell;

	(void)env;
	if (!check_args(ac, av))
		return (1);
	if (!init_mshell(&m_shell))
		return (1);
	str = NULL;
	while (1)
	{
		str = readline("\033[1;33m  Shell  ✗ \033[0m");
		if (str)
		{
			parse_command(str, &m_shell);
		}
		else
			break ;
		free (str);
	}
	return (0);
}
