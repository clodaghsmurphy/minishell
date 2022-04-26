/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 17:22:21 by clmurphy          #+#    #+#             */
/*   Updated: 2022/04/26 18:31:43 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_command(char *str, t_mshell *mshell)
{
	int	i;

	mshell->word = NULL;
	mshell->phrase = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		if (parse_string(&mshell->word, mshell, str, &i) == 2)
			continue ;
		parse_delimiter(&mshell->word, mshell, str, &i);
	}
	assign_tokens(mshell);
}

void	parse_quotes(t_split **word, t_mshell *mshell, char *str, int *i)
{
	int	type;

	if (str[*i] == 34 || str[*i] == 39)
	{
		type = str[*i];
		(*i)++;
		if (str[*i] == '$')
		{			
			parse_dollar_dquotes(word, mshell, str, i);
			return ;
		}
		while (str[*i] != type && str[*i] != '\0')
		{
			split_lstadd_back(word, split_lstnew(str[*i]));
			(*i)++;
		}
		if (str[*i] == '\0')
		{
			printf("quote error\n");
			return ;
		}
		else
		{
			make_word(word, mshell);
			(*i)++;
		}
		if (str[*i] == 32)
		{
			while (str[*i] == 32)
				(*i)++;
		}
	}
}

int	parse_string(t_split **word, t_mshell *mshell, char *str, int *i)
{
	while (is_delim(str, i) == 1)
	{
		printf("is delim %c\n", str[*i]);
		if (str[*i] == 34 || str[*i] == 39)
		{
			parse_quotes(word, mshell, str, i);
			return (2);
		}
		if (str[*i] == '$')
		{
			parse_dollar(word, mshell, str, i);
			return (2);
		}
		split_lstadd_back(word, split_lstnew(str[*i]));
		(*i)++;
	}
	return (1);
}

int	is_delim(char *str, int *i)
{
	if (str[*i] == 32)
		return (0);
	if (str[*i] == '|')
		return (0);
	if (str[*i] == '\0')
		return (0);
	if (str[*i] == '>')
		return (0);
	if (str[*i] == '>')
		return (0);
	if (ft_strncmp(str + *i, ">>", 2) == 0)
		return (0);
	if (ft_strncmp(str + *i, "<<", 2) == 0)
		return (0);
	return (1);
}

void	parse_delimiter(t_split **word, t_mshell *mshell, char *str, int *i)
{
	t_split	*delimiter;
	int		flag;

	flag = 0;
	delimiter = NULL;
	if (str[*i] == '\0')
	{
		make_word(word, mshell);
		return ;
	}
	if (str[*i] == 32)
	{
		while (str[*i] == 32)
			(*i)++;
	}
	if (str[*i] == '|')
	{
		if (str[(*i) + 1] == '|')
		{
			printf("syntax error\n");
			return ;
		}
		split_lstadd_back(&delimiter, split_lstnew(str[*i]));
		flag = 1;
		(*i)++;
		if (str[*i] == 32)
		{
			while (str[*i] == 32)
				(*i)++;
		}
	}
	else if (is_redir(str, i) == 1 || is_redir(str, i) == 2)
	{
		if (is_redir(str, i) == 2)
		{
			split_lstadd_back(&delimiter, split_lstnew(str[*i]));
			(*i)++;
			split_lstadd_back(&delimiter, split_lstnew(str[*i]));

		}
		else
			split_lstadd_back(&delimiter, split_lstnew(str[*i]));
		flag = 1;
		(*i)++;
		if (str[*i] == 32)
		{
			while (str[*i] == 32)
				(*i)++;
		}
	}
	make_word(word, mshell);
	if (flag == 1)
		make_word(&delimiter, mshell);
}

int	is_redir(char *str, int *i)
{
	if (ft_strncmp(str + *i, ">>", 2) == 0)
		return (2);
	if (ft_strncmp(str + *i, "<<", 2) == 0)
		return (2);
	if (str[*i] == '>')
		return (1);
	if (str[*i] == '>')
		return (1);
	
	return (0);
}
