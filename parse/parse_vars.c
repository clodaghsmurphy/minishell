/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:34:17 by clmurphy          #+#    #+#             */
/*   Updated: 2022/05/05 16:55:09 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_dollar(t_split **word, t_mshell *mshell, char *str, int *i)
{
	int		j;
	int		type;
	char	*res;
	char	*var;

	res = NULL;
	var = NULL;
	type = 0;
	j = *i;
	/********define quote type*********/
	if (str[*i - 1] == 34 || str[*i - 1] == 39)
		type = str[*i - 1];
	/*****$ followed by quotes ex $"USER"*******/
	if (quote_after_dollar(word, mshell, str, i) == 1)
		type = str[*i];
	/*****$ with nothing or a delimiter after*******/
	if ((str[*i] == '$' && str[*i + 1] == '\0') || \
	(str[*i] == '$' && str[*i + 1] == ' ') || \
	(str[*i] == '$' && str[*i + 1] == '|'))
	{
		phrase_lstadd_back(&mshell->phrase, phrase_lstnew(ft_strdup("$")));
		(*i)++;
		return ;
	}
	/*****$ followed by a string*******/
	while (is_delim_dollar(str, i) && str[*i] != type)				//\0, |, redirs, quotes and =
	{
		(*i)++;
	/*****$ quotes within $ string*******/
		/*****$ empty quotes in string*******/
		if (str[*i] == 34 || str[*i] == 39 && type == 0)
		{
			type = str[*i];
			(*i)++;
			if (str[*i] == type)
			{
				(*i)++;
				type = 0;
			}
			/*****$ quotes within $ string with possible variables inside*******/
			while (str[*i] != type && str[*i] != '\0')
			{
				if (str[*i] == '$')
				{
					var = is_in_env(mshell, ft_strndup(str + j, (*i - j)));
					if (var != NULL)
						res = ft_strjoin(res, var);
					j = (*i);
					continue ;
				}
				(*i)++;
			}				
		}	
		if (str[*i] == '=')
		{
			var = is_in_env(mshell, ft_strndup(str + j, (*i - j)));
			if (var != NULL)
				res = ft_strjoin(res, var);
			j = (*i);
			while (is_delim_dollar(str, i) && str[*i] != type && str[*i] != '$')
				(*i)++;
			res = ft_strjoin(res, ft_strndup(str + j, (*i - j)));
			j = (*i);
			if (str[*i] == '$')
				continue ;
		}
		/*******condition to see if several $ vars present in string *******/
		if (str[*i] == '$')
		{
			var = is_in_env(mshell, ft_strndup(str + j, (*i - j)));
			if (var != NULL)
				res = ft_strjoin(res, var);
			j = (*i);
			continue ;
		}
	}
	var = is_in_env(mshell, ft_strndup(str + j, (*i - j)));
	if (var != NULL)
		res = ft_strjoin(res, var);
	else
		return ;
	phrase_lstadd_back(&mshell->phrase, phrase_lstnew(res));
	return ;
}

void	parse_dollar_dquotes(t_split **word, t_mshell *mshell, char *str, int *i)
{
	int		j;
	char	type;
	char	*res;
	char	*var;

	type = str[*i - 1];
	j = *i;
	(*i)++;
	if (str[*i] == 34 || str[*i] == 39)
	{
		if (str[*i] == type)
			phrase_lstadd_back(&mshell->phrase, phrase_lstnew(ft_strdup("$")));
		return ;
	}
	while (str[*i] != type && str[*i] != '\0' && str[*i] != '=')
	{
		if (str[*i] == '$' && type == 34)
		{
			var = is_in_env(mshell, ft_strndup(str + j, (*i - j)));
			if (var != NULL)
				res = ft_strjoin(res, var);
			else
				res = ft_strjoin(res, ft_strdup(""));
			j = (*i);
			(*i)++;
			continue ;
		}
		(*i)++;
	}
	if (str[*i] == '\0')
	{
		printf("quote error\n");
		return ;
	}
	if (type == 34)
	{
		var = is_in_env(mshell, ft_strndup(str + j, (*i - j)));
		if (var != NULL)
				res = ft_strjoin(res, var);
		else
			res = ft_strjoin(res, ft_strdup(""));
		phrase_lstadd_back(&mshell->phrase, phrase_lstnew(res));
	}
	else if (type == 39)
	{
		phrase_lstadd_back(&mshell->phrase, phrase_lstnew(ft_strndup2(str + j, (*i - j))));
		(*i)++;
	}
	if (str[*i] == 34)
		(*i)++;
	return ;
}

char	*is_in_env(t_mshell *mshell, char *str)
{
	int		i;
	t_env	*temp;
	char	*var;

	var = ft_strdup(str + 1);
	temp = mshell->env;
	i = 0;
	while (temp != NULL)
	{
		if (ft_strncmp(var, temp->name, 100) == 0)
		{
			free(str);
			free(var);
			return (temp->value);
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

int	is_delim_dollar(char *str, int *i)
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
