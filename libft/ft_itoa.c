/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:25:19 by amontant          #+#    #+#             */
/*   Updated: 2021/11/22 12:25:32 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "stdlib.h"

unsigned int	checkneg(int nbr, int *neg)
{
	if (nbr < 0)
	{
		*neg = 1;
		return (-nbr);
	}
	*neg = 0;
	return (nbr);
}

int	intsize(unsigned int nbr)
{
	int	count;

	count = 1;
	while (nbr > 9)
	{
		count++;
		nbr = nbr / 10;
	}
	return (count);
}

char	*ft_itoa(int value)
{
	unsigned int	i;
	unsigned int	n;
	int				count;
	char			*str;
	int				neg;

	n = checkneg(value, &neg);
	i = n;
	count = intsize(i);
	str = malloc(sizeof(char) * ((count + neg) + 1));
	if (!str)
		return (0);
	i = 0;
	str[count + neg] = '\0';
	while (count > 0)
	{
		str[count - 1 + neg] = '0' + n % 10;
		n = n / 10;
		i++;
		count--;
	}
	if (neg)
		str[0] = '-';
	return (str);
}
