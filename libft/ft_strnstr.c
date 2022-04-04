/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:40:38 by amontant          #+#    #+#             */
/*   Updated: 2021/12/14 17:31:45 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t size)
{
	size_t		i;
	size_t		j;
	int			where;
	char		*p;

	p = (char *)s1;
	i = -1;
	if (s2[0] == '\0')
		return (&p[0]);
	while (s1[++i] && i < size)
	{
		j = 0;
		if (s1[i] == s2[j])
			where = i;
		while (s2[j] && (s1[i] == s2[j]))
		{
			i++;
			j++;
		}
		if (s2[j] == '\0' && i <= size)
			return (&p[where]);
		if (j > 0)
			i = where;
	}
	return (0);
}
