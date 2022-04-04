/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:38:05 by amontant          #+#    #+#             */
/*   Updated: 2021/12/16 11:37:13 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		s_len;
	char	*s_;
	char	*s2;
	int		i;

	i = 0;
	s_ = (char *)s;
	s_len = ft_strlen(s_);
	s2 = malloc(sizeof(char) * s_len + 1);
	if (!s2)
		return (NULL);
	while (s[i])
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
