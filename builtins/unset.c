/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:56:46 by amontant          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/04/13 15:06:27 by clmurphy         ###   ########.fr       */
=======
/*   Updated: 2022/04/13 14:56:18 by amontant         ###   ########.fr       */
>>>>>>> 9f7997886c58acfb8134be2c62903f7c9511f487
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_one(t_env **lst, t_env *to_del);
void	unset_variable(t_env **env, char *variable_name);

void	ft_unset(t_env	**env, char **params)
{
	int	i;

	i = 1;
	if (params[i] == NULL)
		ft_putstr_fd("unset: not enough arguments\n", 2);
	else
	{
		while (params[i])
		{
			unset_variable(env, params[i]);
			i++;
		}
	}
}

void	unset_variable(t_env **env, char *variable_name)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (!ft_strncmp(current->name, variable_name, 2147483647))
		{
			del_one(env, current);
			return ;
		}
		current = current->next;
	}
}
