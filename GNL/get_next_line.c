/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:34:47 by amontant          #+#    #+#             */
/*   Updated: 2022/05/10 13:54:10 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>

char	*save_until_cr(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1] && str[i] != '\n')
	{
		i++;
	}
	if (str[i] == '\n')
		str[i + 1] = 0;
	return (str);
}

void	save_after_cr(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	j = 0;
	if (str[i] == '\n')
		i++;
	while (str[i])
	{
		str[j] = str[i];
		i++;
		j++;
	}
	str[j] = 0;
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*newline;
	int			fin;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, "", 0) == -1)
		return (NULL);
	newline = ft_strdup("");
	newline = ft_strjoin_f_gnl(newline, buff);
	while (ft_strchr_gnl(buff, '\n') == 0)
	{
		fin = read(fd, buff, BUFFER_SIZE);
		buff[fin] = '\0';
		newline = ft_strjoin_f_gnl(newline, buff);
		if (!fin)
			break ;
	}
	if (!fin && newline[0] == 0)
	{
		free(newline);
		return (NULL);
	}
	newline = save_until_cr(newline);
	save_after_cr(buff);
	return (newline);
}
