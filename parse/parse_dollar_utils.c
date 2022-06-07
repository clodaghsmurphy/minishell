/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:34:17 by clmurphy          #+#    #+#             */
/*   Updated: 2022/06/04 12:19:57 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_dollar_dquotes(int type, t_mshell *mshell, char *str, int *i)
{
	mshell->j = *i;
	(*i)++;
	if (dquotes_only(type, mshell, str, i) == 1)
		return ;
	if (eq_start_dquote(mshell, str, i) == 1)
		return ;
	if (digit_in_dquote(mshell, str, i) == 1)
		return ;
	parse_dquote_string(type, mshell, str, i);
	if (eq_in_dquote(mshell, str, i) == 1)
		return ;
	free(mshell->var);
	mshell->var = NULL;
	return ;
}

char	*is_in_env(t_mshell *mshell, char *str)
{
	int		i;
	t_env	*temp;
	char	*var;

	if (str[0] == '$')
		var = ft_strdup(str + 1);
	else
		var = ft_strdup(str);
	temp = mshell->env;
	i = 0;
	while (temp != NULL)
	{
		if (ft_strncmp(var, temp->name, 100) == 0)
		{
			free(str);
			free(var);
			return (ft_strdup(temp->value));
		}
		temp = temp->next;
	}
	free(str);
	free(var);
	return (NULL);
}

char	*ft_strndup(const char *s, int size)
{
	int		s_len;
	char	*s_;
	char	*s2;
	int		i;

	i = 0;
	s_ = (char *)s;
	s_len = ft_strlen(s_);
	s2 = malloc(sizeof(char) * s_len + 1);
	if (!s2)
		return (NULL);
	while (s[i] && i < size)
	{
		s2[i] = s[i];
		i++;
		if (s[i] == '$')
			break ;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strndup2(const char *s, int size)
{
	int		s_len;
	char	*s_;
	char	*s2;
	int		i;

	i = 0;
	s_ = (char *)s;
	s_len = ft_strlen(s_);
	s2 = malloc(sizeof(char) * s_len + 1);
	if (!s2)
		return (NULL);
	while (s[i] && i < size)
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

int	is_delim_dollar(char *str, int i)
{
	if (str[i] == 32)
		return (0);
	if (str[i] == '|')
		return (0);
	if (str[i] == '=')
		return (0);
	if (str[i] == '\0')
		return (0);
	if (str[i] == '>')
		return (0);
	if (str[i] == '>')
		return (0);
	if (ft_strncmp(str + i, ">>", 2) == 0)
		return (0);
	if (ft_strncmp(str + i, "<<", 2) == 0)
		return (0);
	return (1);
}
