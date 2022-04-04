/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:33:24 by amontant          #+#    #+#             */
/*   Updated: 2021/12/14 18:12:15 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*_s1;
	unsigned char	*_s2;

	_s1 = (unsigned char *)s1;
	_s2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n && _s1[i] == _s2[i])
	{
		i++;
	}
	if (i == n)
		return (0);
	return (_s1[i] - _s2[i]);
}
