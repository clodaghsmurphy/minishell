/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:34:28 by clmurphy          #+#    #+#             */
/*   Updated: 2022/05/12 16:21:16 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_command(char *str, t_mshell *mshell)
{
	mshell->command = NULL;
	if (!str)
		return (-1);
	if (ft_strncmp(str, "", 10) == 0)
		return (0);
	split_command(str, mshell);
	if (mshell->q_error != 1 && mshell->s_error != 1)
	{
		mshell->command = create_command(mshell);
		free_phrase(&mshell->phrase);
		ft_exe(mshell);
	}
	free_command(&mshell->command);
	return (0);
}

void	split_command(char *str, t_mshell *mshell)
{
	int	i;

	mshell->word = NULL;
	mshell->phrase = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		parse_delimiter(&mshell->word, mshell, str, &i);
		if (parse_string(&mshell->word, mshell, str, &i) == 2)
			continue ;
		parse_delimiter(&mshell->word, mshell, str, &i);
	}
}

t_command	*create_command(t_mshell *mshell)
{
	t_phrase	*temp_phrase;
	t_command	*command;
	t_command	*temp_command;
	int			size;
	int			i;

	command = NULL;
	command_lstadd_back(&command, command_lstnew(NULL));
	temp_command = command;
	temp_phrase = mshell->phrase;
	while (temp_phrase != NULL)
	{
		i = 0;
		size = phrase_lstsize(temp_phrase);
		temp_command->value = (char **)malloc(sizeof(char *) * (size + 1));
		while (temp_phrase != NULL && \
		ft_strncmp(temp_phrase->str, "|", 10) != 0)
		{
			temp_command->value[i] = temp_phrase->str;
			i++;
			temp_phrase = temp_phrase->next;
		}
		if (temp_phrase != NULL && ft_strncmp(temp_phrase->str, "|", 10) == 0)
		{
			temp_command->value[i] = 0;
			temp_phrase = temp_phrase->next;
			if (temp_phrase == NULL)
				break ;
			command_lstadd_back(&command, command_lstnew(NULL));
			temp_command = temp_command->next;
		}
		else
		{
			temp_command->value[i] = 0;
			temp_command->next = NULL;
			break ;
		}
	}
	return (command);
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
