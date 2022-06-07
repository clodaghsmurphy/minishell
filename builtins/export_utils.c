/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiloub <shiloub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:57:12 by amontant          #+#    #+#             */
/*   Updated: 2022/06/07 22:45:27 by shiloub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_rm_double(t_env **env)
{
	t_env	*i;
	t_env	*j;
	t_env	*save;

	i = *env;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (!ft_strncmp(i->name, j->name, ft_strlen(i->name) + 1))
			{
				save = i;
				i = i->next;
				del_one(env, save);
			}
			j = j->next;
		}
		i = i->next;
	}
}

int	check_valid_variable(char *variable)
{
	int	i;

	i = 0;
	if (char_is_digit(variable[i]))
		return (2);
	while (variable[i])
	{
		if (!is_alpha_num(variable[i]) && variable[i] != '=')
			return (2);
		if (variable[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*get_name(char *line)
{	
	int		i;
	char	*name;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	name = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (line[i] && line[i] != '=')
	{
		name[i] = line[i];
		i++;
	}
	name[i] = 0;
	return (name);
}

char	*get_value(char *line)
{	
	int		i;
	int		count;
	char	*value;

	i = 0;
	count = 0;
	while (line[i] && line[i] != '=')
		i++;
	while (line[i + count])
		count ++;
	value = malloc(sizeof(char) * (count));
	count = 0;
	i++;
	while (line[i])
	{
		value[count] = line[i];
		i++;
		count ++;
	}
	value[count] = 0;
	return (value);
}
