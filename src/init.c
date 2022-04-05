/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:26:06 by clmurphy          #+#    #+#             */
/*   Updated: 2022/04/05 14:47:51 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_mshell(t_mshell *mshell)
{
	mshell = malloc(sizeof(t_mshell));
	if (!mshell)
		return (-1);
	mshell->command = malloc(sizeof(t_command));
	if (!mshell->command)
		return (-1);
	return (1);
}
