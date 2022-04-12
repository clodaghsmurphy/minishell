/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:26:06 by clmurphy          #+#    #+#             */
/*   Updated: 2022/04/12 11:18:48 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_mshell(t_mshell *mshell)
{
	armsignals();
	mshell = ft_calloc(sizeof(t_mshell), 1);
	if (!mshell)
		return (-1);
	mshell->command = ft_calloc(sizeof(t_command), 1);
	if (!mshell->command)
		return (-1);
	mshell->command = NULL;
	return (1);
}
