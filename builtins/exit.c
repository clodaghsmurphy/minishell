/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiloub <shiloub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:00:11 by amontant          #+#    #+#             */
/*   Updated: 2022/05/18 14:02:51 by shiloub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **params, t_mshell *mini)
{
	int	code;

	code = 0;
	if (params[1])
		code = ft_atoi(params[1]);
	free_mini(mini);
	ft_putstr_fd("exit\n", 1);
	exit(code);
}
