/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:34:28 by clmurphy          #+#    #+#             */
/*   Updated: 2022/04/13 16:34:43 by amontant         ###   ########.fr       */
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
	ft_exe(mshell);
	return (0);
}

void	create_command(t_mshell *mshell)
{
	t_phrase	*temp_phrase;
	t_command	*temp_command;
	int			size;
	int			i;

	i = 0;
	command_lstadd_back(&mshell->command, command_lstnew(NULL));
	temp_command = mshell->command;
	temp_phrase = mshell->phrase;
	while (temp_phrase != NULL)
	{
		i = 0;
		size = phrase_lstsize(mshell->phrase);
		temp_command->value = malloc(sizeof(char) * size + 1);
		while (temp_phrase != NULL && strncmp(temp_phrase->str, "|", 10) != 0)
		{
			temp_command->value[i] = malloc(sizeof(char) * \
			ft_strlen(temp_phrase->str) + 1);
			temp_command->value[i] = temp_phrase->str;
			i++;
			temp_phrase = temp_phrase->next;
		}
		temp_command->value[i] = 0;
		command_lstadd_back(&mshell->command, command_lstnew(NULL));
		temp_command = temp_command->next;
		if (temp_phrase != NULL)
			temp_phrase = temp_phrase->next;
	}
	print_command(mshell);
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
