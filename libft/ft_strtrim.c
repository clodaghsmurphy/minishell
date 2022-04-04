/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:41:13 by amontant          #+#    #+#             */
/*   Updated: 2021/11/22 12:41:15 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	strchrchar(const char *str, char c)
{
	int	i;
	int	find;

	i = 0;
	find = 0;
	while (str[i])
	{
		if (str[i] == c)
			find = 1;
		i++;
	}
	return (find);
}

int	checkstart(char const *s, char const *set)
{
	int	count;

	count = 0;
	while (strchrchar(set, s[count]))
		count++;
	return (count);
}

int	checkend(char const *s, char const *set)
{
	int	count;
	int	i;

	count = 0;
	i = ft_strlen((char *)s) - 1;
	while (strchrchar(set, s[i]))
	{
		count++;
		i--;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*str;
	int		strsize;
	int		j;

	strsize = ft_strlen((char *)s1) - checkstart(s1, set) - checkend(s1, set);
	if (ft_strlen(s1) > checkstart(s1, set))
		str = malloc(sizeof(char) * strsize + 1);
	else
		str = malloc(sizeof(char));
	if (!str)
		return (NULL);
	i = checkstart(s1, set);
	j = 0;
	if (ft_strlen(s1) > checkstart(s1, set))
	{
		while (i < (ft_strlen((char *)s1) - checkend(s1, set)))
		{
			str[j] = s1[i];
			j++;
			i++;
		}
	}
	str[j] = '\0';
	return (str);
}
