/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:22:15 by clmurphy          #+#    #+#             */
/*   Updated: 2022/05/27 19:44:35 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	next_phrase(int *i, t_phrase **temp_phrase, t_command *temp_command)
{
	temp_command->value[*i] = ft_strdup((*temp_phrase)->str);
	free((*temp_phrase)->str);
	(*i)++;
	*temp_phrase = (*temp_phrase)->next;
	return (0);
}

int	next_command(int *i, t_phrase **temp_phrase, t_command **temp_command, \
t_command **command)
{
	(*temp_command)->value[*i] = 0;
	free((*temp_phrase)->str);
	(*temp_phrase) = (*temp_phrase)->next;
	if (temp_phrase == NULL)
		return (1);
	command_lstadd_back(command, command_lstnew(NULL));
	(*temp_command) = (*temp_command)->next;
	return (0);
}

int	check_args(int ac, char **av)
{
	if (ac != 1)
	{
		printf("%s %s directory not found\n", av[0], av[1]);
		exit(0);
	}
	return (1);
}

char	*ft_strjoin_f2(char *s1, char const *s2)
{
	int		lens1;
	char	*strcat;
	int		i;

	if (!s1)
		s1 = ft_strdup("");
	lens1 = ft_strlen((char *)s1);
	i = 0;
	strcat = malloc(sizeof(char) * (lens1 + ft_strlen((char *)s2) + 1));
	if (!strcat)
		return (0);
	while (s1[i])
	{
		strcat[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		strcat[i + lens1] = s2[i];
		i++;
	}
	strcat[i + lens1] = '\0';
	free(s1);
	return (strcat);
}

void	free_phrase2(t_phrase **phrase)
{
	t_phrase	*current;
	t_phrase	*temp;

	if (*phrase == NULL)
		return ;
	current = *phrase;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		if (temp->str)
			free(temp->str);
		free(temp);
	}
	*phrase = NULL;
}
