/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lataille.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiloub <shiloub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 23:56:57 by shiloub           #+#    #+#             */
/*   Updated: 2022/06/03 23:57:06 by shiloub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lataille(char **command)
{
	int		i;
	int		found;

	found = 0;
	i = 0;
	while (command[i])
	{
		if ((!ft_strncmp(">>", command[i], 3) || \
			!ft_strncmp(">", command[i], 2)) && found == 0)
		{
			if (command[i + 1])
				found = 1;
		}
		i++;
	}
	if (found)
		return (i - 1);
	return (i + 1);
}
