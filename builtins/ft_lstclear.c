/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:28:16 by amontant          #+#    #+#             */
/*   Updated: 2021/11/22 12:28:19 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*temp;

	if (*lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		del(current->content);
		temp = current;
		current = current->next;
		free(temp);
	}
	*lst = NULL;
}
