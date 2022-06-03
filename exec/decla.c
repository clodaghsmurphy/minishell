/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decla.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiloub <shiloub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 00:16:53 by shiloub           #+#    #+#             */
/*   Updated: 2022/06/04 00:33:19 by shiloub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	decla_v2(int *i, int *j, int *found, char **command)
{
	int	holaquetal;

	holaquetal = 0;
	*found = 0;
	*i = 0;
	*j = 0;
	while (command[holaquetal])
		holaquetal++;
	return (holaquetal);
}

int	decla(int *i, int *j, int *found, char **command)
{
	int	salut;

	*i = 0;
	*found = 0;
	salut = 0;
	*j = 0;
	while (command[salut])
		salut ++;
	return (salut);
}

void	init_things_to_save_two_little_lines_for_norme(int *i, \
int *j, int *found)
{
	*i = 0;
	*j = 0;
	*found = 0;
}
