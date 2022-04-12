/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:34:28 by clmurphy          #+#    #+#             */
/*   Updated: 2022/04/12 12:05:42 by clmurphy         ###   ########.fr       */
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
	char		**tab;
	int			size;
	int			i;

	i = 0;
	size = phrase_lstsize(mshell->phrase) - count_delim(&mshell->phrase);
	temp_phrase = mshell->phrase;
	while (temp_phrase != NULL)
	{
		while (temp_phrase != NULL && strncmp(temp_phrase->str, "|", 10) != 0)
		{
			tab = malloc(sizeof(char ) * size);
			if (!tab)
				return ;
			tab[i] = malloc(sizeof(char) * ft_strlen(temp_phrase->str));
			if (!tab[i])
				return ;
			tab[i] = temp_phrase->str;
			printf("tab is %s\n", tab[i]);
			i++;
			temp_phrase = temp_phrase->next;
		}
		command_lstadd_back(&mshell->command, command_lstnew(tab));
		freetab(tab);
		if (temp_phrase != NULL)
			temp_phrase = temp_phrase->next;
	}
	print_command(&mshell->command, size);
	printf("after tab");
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
