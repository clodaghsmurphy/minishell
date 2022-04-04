/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:38:47 by amontant          #+#    #+#             */
/*   Updated: 2021/12/14 17:29:06 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t		i;
	char		*src_;

	i = 0;
	if (!src)
		return (0);
	src_ = (char *)src;
	if (!size)
		return (ft_strlen(src));
	while (i < size && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	if (i == size)
		dest[size - 1] = '\0';
	else
		dest[i] = '\0';
	return (ft_strlen(src_));
}
