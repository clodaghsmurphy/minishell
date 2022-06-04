/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 11:37:50 by clmurphy          #+#    #+#             */
/*   Updated: 2022/06/04 11:37:53 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redir_in	*parse_redir_in(char **command)
{
	t_redir_in	*lst;
	char		**tab;
	int			i;

	i = 0;
	lst = NULL;
	tab = ft_dup_tab(command);
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], "<<", 3) && tab[i + 1])
		{
			add_back_redir_in(&lst, tab[i + 1], 1);
			tab = command_clear_one_in(tab);
			i = i - 1;
		}
		else if (!ft_strncmp(tab[i], "<", 2) && tab[i + 1])
		{
			add_back_redir_in(&lst, tab[i + 1], 0);
			tab = command_clear_one_in(tab);
			i = i - 1;
		}
		i++;
	}
	free_tab(tab);
	return (lst);
}

void	add_back_redir_in(t_redir_in **lst, char *file_name, int bol)
{
	t_redir_in	*new;
	t_redir_in	*current;

	new = malloc(sizeof(t_redir_in));
	new->name = ft_strdup(file_name);
	new->type = bol;
	new->stop = NULL;
	new->next = NULL;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new;
}

char	**command_clear_all_in(char **command)
{
	char	**new;
	int		i;
	int		j;
	int		found;

	new = malloc(sizeof(char *) * (decla(&i, &j, &found, command) + 1));
	while (command[i])
	{
		if ((!ft_strncmp("<<", command[i], 3) || \
			!ft_strncmp("<", command[i], 2)))
		{
			if (command[i + 1])
				i += 2;
		}
		else
		{
			new[j] = ft_strdup(command[i]);
			j++;
			i++;
		}
	}
	new[j] = 0;
	free_tab(command);
	return (new);
}

char	**command_clear_one_in(char **command)
{
	char	**new;
	int		i;
	int		j;
	int		found;

	new = malloc(sizeof(char *) * (decla_v2(&i, &j, &found, command) + 1));
	while (command[i])
	{
		if ((!ft_strncmp("<<", command[i], 3) || \
			!ft_strncmp("<", command[i], 2)) && found == 0)
		{
			if (command[i + 1])
			{
				found = 1;
				i += 2;
			}
		}
		else
			new[j++] = ft_strdup(command[i++]);
	}
	new[j] = 0;
	free_tab(command);
	return (new);
}
