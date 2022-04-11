/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:34:28 by clmurphy          #+#    #+#             */
/*   Updated: 2022/04/11 17:08:24 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_command(char *str, t_mshell *mshell)
{
	mshell->command = NULL;
	if (!str)
		return (-1);
	split_command(str, mshell);
	create_command(mshell);
	return (0);
}

void	create_command(t_mshell *mshell)
{
	t_phrase	*temp_phrase;
	t_command	*temp_command;
	int			size;
	int			i;

	i = 0;
	size = phrase_lstsize(mshell->phrase);
	temp_phrase = mshell->phrase;
	temp_command = mshell->command;
	mshell->command->value = malloc(sizeof(char ) * size);
	if (!mshell->command->value)
		return ;
	while (temp_phrase != NULL)
	{
		if (strncmp(temp_phrase->str, "|", 10) != 0)
		{
			mshell->command->value[i] = malloc(sizeof(char) * ft_strlen(temp_phrase->str));
			if (!mshell->command->value[i])
				return ;
			mshell->command->value[i] = temp_phrase->str;
			i++;
		}
		else
		{
			temp_command = temp_command->next;
		}
		temp_phrase = temp_phrase->next;
	}
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
