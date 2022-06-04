/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 11:37:14 by clmurphy          #+#    #+#             */
/*   Updated: 2022/06/04 11:37:34 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redir_out	*parse_redir_out(char **command)
{
	t_redir_out	*lst;
	char		**tab;
	int			i;

	i = 0;
	lst = NULL;
	tab = ft_dup_tab(command);
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], ">>", 3) && tab[i + 1])
		{
			add_back_redir_out(&lst, tab[i + 1], 1);
			tab = command_clear_one(tab);
			i = i - 1;
		}
		else if (!ft_strncmp(tab[i], ">", 2) && tab[i + 1])
		{
			add_back_redir_out(&lst, tab[i + 1], 0);
			tab = command_clear_one(tab);
			i = i - 1;
		}
		i++;
	}
	free_tab(tab);
	return (lst);
}

char	**ft_dup_tab(char **command)
{
	int		i;
	char	**dup;

	i = 0;
	while (command[i])
		i++;
	dup = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (command[i])
	{
		dup[i] = ft_strdup(command[i]);
		i++;
	}
	dup[i] = 0;
	return (dup);
}

char	**command_clear_all_out(char **command)
{
	char	**new;
	int		i;
	int		j;
	int		found;

	init_things_to_save_two_little_lines_for_norme(&i, &j, &found);
	while (command[i])
		i ++;
	new = malloc(sizeof(char *) * (i + 1));
	i = 0;
	j = 0;
	while (command[i])
	{
		if ((!ft_strncmp(">>", command[i], 3) || \
			!ft_strncmp(">", command[i], 2)))
		{
			if (command[i + 1])
				i += 2;
		}
		else
			new[j++] = ft_strdup(command[i++]);
	}
	new[j] = 0;
	free_tab(command);
	return (new);
}

char	**command_clear_one(char **command)
{
	char	**new;
	int		i;
	int		j;
	int		found;

	new = malloc(sizeof(char *) * lataille(command));
	init_things_to_save_two_little_lines_for_norme(&i, &j, &found);
	while (command[i])
	{
		if ((!ft_strncmp(">>", command[i], 3) || \
			!ft_strncmp(">", command[i], 2)) && found == 0)
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

void	add_back_redir_out(t_redir_out **lst, char *file_name, int bol)
{
	t_redir_out	*new;
	t_redir_out	*current;

	new = malloc(sizeof(t_redir_out));
	new->name = ft_strdup(file_name);
	new->append = bol;
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
