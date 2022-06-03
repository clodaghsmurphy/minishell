/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiloub <shiloub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 23:10:50 by shiloub           #+#    #+#             */
/*   Updated: 2022/06/03 23:11:04 by shiloub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_redir_in(t_redir_in *lst)
{
	t_redir_in	*temp;

	while (lst)
	{
		temp = lst;
		free(lst->name);
		free(lst->stop);
		lst = lst->next;
		free(temp);
	}
}

void	free_redir_out(t_redir_out *lst)
{
	t_redir_out	*temp;

	while (lst)
	{
		temp = lst;
		free(lst->name);
		lst = lst->next;
		free(temp);
	}
}

void	free_mini(t_mshell *mini)
{
	free(mini->pipe_fd);
	mini->pipe_fd = NULL;
	free_command(&mini->command);
	mini->command = NULL;
	env_free(mini->env);
	free(mini->pids);
	mini->pids = NULL;
	free(mini);
}
