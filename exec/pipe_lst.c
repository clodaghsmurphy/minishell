/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:37:14 by amontant          #+#    #+#             */
/*   Updated: 2022/04/18 17:10:14 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// t_pipe	*set_lst_pipe(t_command *command)
// {
// 	t_pipe	*lst_pipe;

// 	lst_pipe = NULL;
// 	while (command)
// 	{
// 		add_back_pipe(&lst_pipe);
// 		command = command->next;
// 	}
// 	return (lst_pipe);
// }

// t_pipe	add_back_pipe(t_pipe *pipe)
// {
// 	t_pipe	*new;
// 	t_pipe	*temp;

// 	temp = pipe;
// 	new = malloc(sizeof(t_pipe));
// 	if (!new)
// 		return ;
// 	new->next = NULL;
// 	if (pipe == NULL || *pipe == NULL)
// 		pipe = &new;
// 	else
// 	{
// 		while (temp)
// 			temp = temp->next;
// 		temp->next = new;
// 	}
// }
