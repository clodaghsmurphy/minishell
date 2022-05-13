/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:22:15 by clmurphy          #+#    #+#             */
/*   Updated: 2022/05/13 11:37:44 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	next_phrase(int *i, t_phrase **temp_phrase, t_command **temp_command)
{
	(*temp_command)->value[*i] = (*temp_phrase)->str;
	(*i)++;
	*temp_phrase = (*temp_phrase)->next;
	return (0);
}

int	next_command(int *i, t_phrase *temp_phrase, t_command *temp_command, \
t_command *command)
{
	temp_command->value[*i] = 0;
	temp_phrase = temp_phrase->next;
	if (temp_phrase == NULL)
		return (1);
	command_lstadd_back(&command, command_lstnew(NULL));
	temp_command = temp_command->next;
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
