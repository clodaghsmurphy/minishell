/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiloub <shiloub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:38:20 by amontant          #+#    #+#             */
/*   Updated: 2022/06/03 22:45:37 by shiloub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"

void	ft_putstr_no_quote(char *str)
{
	int		i;
	char	*var;

	i = 0;
	var = delim_q(str);
	while (var[i])
	{
		ft_putchar_fd(var[i], 1);
		i++;
	}
	free(var);
}

void	echo(char **args)
{
	int	arg;
	int	i;

	arg = get_opt(args);
	i = arg + 1;
	while (args[i] != NULL)
	{
		ft_putstr_no_quote(args[i]);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (arg == 0)
		ft_putchar_fd('\n', 1);
	g_estatus = 0;
}

int	get_opt(char **args)
{
	int	arg;
	int	i;

	arg = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_opt(args[i]))
			return (arg);
		else
		{
			arg ++;
		}
		i++;
	}
	return (arg);
}

int	is_valid_opt(char *arg)
{
	int	valid;
	int	i;

	valid = 1;
	i = 0;
	if (!arg[0] || !arg[1] || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i += 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
