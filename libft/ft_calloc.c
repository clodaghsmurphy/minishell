/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:22:09 by amontant          #+#    #+#             */
/*   Updated: 2021/12/14 15:53:24 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	char	*mem;

	mem = malloc(nmemb * (size));
	if (!mem)
		return (NULL);
	i = 0;
	while (i < size * nmemb)
	{
		mem[i] = 0;
		i++;
	}
	return (mem);
}
