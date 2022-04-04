/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:38:33 by amontant          #+#    #+#             */
/*   Updated: 2021/12/16 12:05:45 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*blup(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while ((j + i) < n && src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	if ((j + i) == n)
	{
		dest[i + j - 1] = '\0';
	}
	else
		dest[i + j] = '\0';
	return (dest);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	int		srclen;
	size_t	destlen;
	char	*src_;

	src_ = (char *)src;
	destlen = ft_strlen(dest);
	srclen = ft_strlen(src_);
	if (size <= destlen)
		return (srclen + size);
	else
	{
		dest = blup(dest, src, size);
	}
	return (destlen + srclen);
}
