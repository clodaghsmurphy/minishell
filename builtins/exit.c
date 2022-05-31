/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:00:11 by amontant          #+#    #+#             */
/*   Updated: 2022/05/31 15:30:04 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_str_is_only_digit(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}


void	ft_exit(char **params, t_mshell *mini)
{
	int	code;

	code = 0;
	ft_putstr_fd("exit\n", 1);
	if (params[1])
	{
		if (!ft_str_is_only_digit(params[1]))
		{
			ft_putstr_fd("exit : numeric argument required\n", 2);
			code = 2;
		}
		else if (params[2])
		{
			ft_putstr_fd("exit : too many arguments\n", 2);
			return ;
		}
		else
			code = ft_atoi(params[1]);
	}
	free_mini(mini);
	exit(code);
}

int	simul_ft_exit(char **params, t_mshell *mini)
{
	int	code;

	code = 0;
	if (params[1])
	{
		if (params[2])
			return (1);
		code = ft_atoi(params[1]);
		if (!ft_str_is_only_digit(params[1]))
			code = 2;
	}
	return(code);
}
