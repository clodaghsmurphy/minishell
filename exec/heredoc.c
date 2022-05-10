/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 12:27:24 by amontant          #+#    #+#             */
/*   Updated: 2022/05/06 13:28:19 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_heredoc(t_redir_in *lst, t_redir_in *to_change, char *hd_name)
{
	t_redir_in	*current;
	
	current = lst;
	while (current && current != to_change)
		current = current->next;
	free(current->name);
	current->name = ft_strdup(hd_name);
	current->type = 0;
}

char	*get_hd_name(void)
{
	char	*hd;
	int		i;

	i = 0;
	hd = ft_strdup(".hd");
	while (!access(hd, F_OK) && i < 300)
	{
		hd = ft_strjoin_f(hd, ft_atoi(i));
		i++;
	}
	if (access(hd, F_OK))
		return (hd);
	free(hd);
	return (NULL);
}