/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:38:20 by amontant          #+#    #+#             */
/*   Updated: 2022/04/04 16:40:42 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

int	is_valid_opt(char *arg);
int	get_opt(char **args);

void	echo(char **args)
{
	int	arg;
	int	i;

	arg = get_opt(args);
	i = 0;
	if (arg == 0)
	{
		while (args[i] != NULL)
		{
			ft_putstr(args[i]);
			i++;
		}
		ft_putchar("\n");
	}
	else
	{
		i = arg;
		while (args[i])
		{
			ft_putstr(args[i]);
			i++;
		}
	}
}

int	get_opt(char **args)
{
	int	arg;
	int	i;

	arg = 0;
	i = 0;
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

int	main(int ac, char **av)
{
	char **av_null;

	av_null = malloc(size_of(char *) * (ac));
	av_null[ac - 1] = NULL;
	while (ac > 1)
	{
		av_null[ac - 2] = av[ac - 1];
		ac --;
	}

	
}
