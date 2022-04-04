/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:31:08 by amontant          #+#    #+#             */
/*   Updated: 2021/11/22 12:31:10 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*newelem;
	t_list	*newlist;

	newlist = NULL;
	current = lst;
	while (current != NULL)
	{
		newelem = ft_lstnew(f(current->content));
		if (!newelem)
		{
			ft_lstclear(&newlist, (*del));
			return (NULL);
		}
		ft_lstadd_back(&newlist, newelem);
		current = current->next;
	}
	return (newlist);
}
