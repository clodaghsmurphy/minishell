/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:32:48 by amontant          #+#    #+#             */
/*   Updated: 2021/12/12 15:33:18 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char			*dest_;
	const char		*src_;
	size_t			i;

	dest_ = (char *)dest;
	src_ = (char *)src;
	i = 0;
	if ((src_ < dest_ && src_ + n > dest_))
	{
		while (i < n)
		{
			dest_[n - i - 1] = src_[n - i - 1];
			i++;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
