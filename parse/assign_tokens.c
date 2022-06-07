/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:13:20 by clmurphy          #+#    #+#             */
/*   Updated: 2022/06/04 12:11:01 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* 
void	assign_tokens(t_mshell *mshell)
{
	t_phrase	*temp;

	temp = mshell->phrase;
	while (temp != NULL)
	{
		if (is_builtin(temp->str))
			temp->token = builtin;
		else if (ft_strncmp(temp->str, "|", 10) == 0)
			temp->token = PIPE;
		else if (ft_strncmp(temp->str, "<", 10) == 0)
			temp->token = redir_in;
		else if (ft_strncmp(temp->str, ">", 10) == 0)
			temp->token = redir_out;
		else if (ft_strncmp(temp->str, ">", 10) == 0)
			temp->token = redir_out;
		else if (ft_strncmp(temp->str, "<<", 10) == 0)
			temp->token = here_doc;
		else if (is_variable(temp->str))
			temp->token = d_variable;
		else
			temp->token = string;
		temp = temp->next;
	}
} */

int	is_builtin(char *str)
{
	if (ft_strncmp(str, "echo", 100) == 0)
		return (1);
	else if (ft_strncmp(str, "cd", 100) == 0)
		return (1);
	else if (ft_strncmp(str, "pwd", 100) == 0)
		return (1);
	else if (ft_strncmp(str, "export", 100) == 0)
		return (1);
	else if (ft_strncmp(str, "unset", 100) == 0)
		return (1);
	else if (ft_strncmp(str, "env", 100) == 0)
		return (1);
	else if (ft_strncmp(str, "exit", 100) == 0)
		return (1);
	else
		return (0);
}

int	is_variable(char *str)
{
	if (str[0] == '$')
		return (1);
	else
		return (0);
}

void	if_word_free_word(t_split **word)
{
	if (*word)
	{
		ft_wordclear(word);
		*word = NULL;
	}
}
