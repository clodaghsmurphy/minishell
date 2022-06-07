/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lataille.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 23:56:57 by shiloub           #+#    #+#             */
/*   Updated: 2022/06/07 19:47:59 by clmurphy         ###   ########.fr       */
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

void	end_fonction(t_mshell *mini)
{
	delete_hd(mini->command);
	free(mini->pipe_fd);
	free_command(&mini->command);
	armsignals();
}

int	exit_if_pas_de_commande(t_mshell *mini)
{
	if (mini->command->value[0] == NULL)
	{
		delete_hd(mini->command);
		free(mini->pipe_fd);
		free_command(&mini->command);
		armsignals();
		return (1);
	}
	return (0);
}
