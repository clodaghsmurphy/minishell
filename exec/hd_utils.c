/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiloub <shiloub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 23:26:28 by shiloub           #+#    #+#             */
/*   Updated: 2022/06/03 23:26:47 by shiloub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_heredoc(t_redir_in *to_change, char *hd_name)
{
	to_change->stop = ft_strjoin(to_change->name, "\n");
	free(to_change->name);
	to_change->name = ft_strdup(hd_name);
	to_change->type = 0;
}

char	*get_hd_name(void)
{
	char	*hd;
	int		i;
	char	*base;
	char	*temp;

	i = 0;
	base = ft_strdup(".hd");
	hd = ft_strdup(base);
	while (!access(hd, F_OK) && i < 300)
	{
		free(hd);
		temp = ft_itoa(i);
		hd = ft_strjoin(base, temp);
		free(temp);
		i++;
	}
	free(base);
	if (access(hd, F_OK))
		return (hd);
	free(hd);
	return (NULL);
}

void	find_replace_hd(t_redir_in *lst)
{
	t_redir_in	*current;
	char		*str;
	int			hd_fd;

	current = lst;
	while (current)
	{
		if (current->type == 1)
		{
			str = get_hd_name();
			replace_heredoc(current, str);
			hd_fd = open(str, O_CREAT, 0666);
			close(hd_fd);
			free(str);
		}
		current = current->next;
	}
}
