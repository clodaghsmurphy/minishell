/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:34:28 by clmurphy          #+#    #+#             */
/*   Updated: 2022/06/07 17:54:36 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_command(char *str, t_mshell *mshell)
{
	mshell->command = NULL;
	if (!str)
		return (-1);
	if (ft_strncmp(str, "", 10) == 0)
		return (0);
	split_command(str, mshell);
	check_serror(&mshell->phrase, mshell);
	if (mshell->s_error != 1 && mshell->phrase != NULL)
	{
		mshell->command = create_command(mshell);
		free_phrase(&mshell->phrase);
		ft_exe(mshell);
	}
	else
	{
		free_phrase2(&mshell->phrase);
		free_command(&mshell->command);
	}
	return (0);
}

void	check_serror(t_phrase **phrase, t_mshell *mshell)
{
	t_phrase	*temp;
	int			i;

	i = 0;
	temp = *phrase;
	if (!temp)
		return ;
	while (temp->next != NULL)
		temp = temp->next;
	if (temp->str[i] == '|' )
		syntax_error(mshell);
	if (temp->str[i] == '<' )
		syntax_error(mshell);
	if (temp->str[i] == '>' )
		syntax_error(mshell);
}

void	split_command(char *str, t_mshell *mshell)
{
	int	i;

	mshell->word = NULL;
	mshell->phrase = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		parse_delimiter(mshell, str, &i);
		if (parse_string(&mshell->word, mshell, str, &i) == 2)
			continue ;
		parse_delimiter(mshell, str, &i);
	}
}

t_command	*create_command(t_mshell *mshell)
{
	t_phrase	*temp_phrase;
	t_command	*command;

	command = NULL;
	command_lstadd_back(&command, command_lstnew(NULL));
	temp_phrase = mshell->phrase;
	parse_command_list(temp_phrase, &command);
	return (command);
}

int	parse_command_list(t_phrase *temp_phrase, t_command **command)
{
	int			i;
	int			size;
	t_command	*temp_command;

	temp_command = *command;
	while (temp_phrase != NULL)
	{
		if (init_values(&i, &size, &temp_command, &temp_phrase) == -1)
			return (-1);
		while (temp_phrase != NULL && \
		ft_strncmp(temp_phrase->str, "|", 10) != 0)
			next_phrase(&i, &temp_phrase, temp_command);
		if (temp_phrase != NULL && ft_strncmp(temp_phrase->str, "|", 10) == 0)
		{
			if (next_command(&i, &temp_phrase, &temp_command, command) == 1)
				break ;
		}
		else
		{
			temp_command->value[i] = 0;
			temp_command->next = NULL;
			break ;
		}
	}
	return (0);
}
