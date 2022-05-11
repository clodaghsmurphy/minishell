/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mshell->vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:34:17 by clmurphy          #+#    #+#             */
/*   Updated: 2022/05/10 12:01:10 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_dollar(t_split **word, t_mshell *mshell, char *str, int *i)
{
	int		j;
	int		type;
	int		res;

	j = *i;
	if (*word)
		mshell->res = ft_strjoin(mshell->res, make_word(word, mshell));
	if (quote_after_dollar(word, mshell, str, i) == 1)
		return ;
	if (dollar_only(word, mshell, str, i) == 1)
		return ;
	if (str[*i + 1] == '=')
	{
		(*i)++;
		(*i)++;
		mshell->res = ft_strjoin(mshell->res, ft_strdup("$="));
		return ;
	}
	if (str[*i + 1] >= '0' && str[*i + 1] <= '9')
	{
		(*i)++;
		mshell->var = is_in_env(mshell, ft_strndup(str + j, (*i - j)));
		if (mshell->var != NULL)
			mshell->res = ft_strjoin(mshell->res, mshell->var);
		else
		{
			free(mshell->var);
			mshell->var = NULL;
			return ;
		}
	}
	res = parse_dollar_string(&j, mshell, str, i);
	if (res == 1)
		return ;
	else if (res == 2)
	{
		mshell->var = is_in_env(mshell, ft_strndup(str + j, (*i - j)));
		if (mshell->var != NULL)
			mshell->res = ft_strjoin(mshell->res, mshell->var);
		else
		{
			free(mshell->var);
			mshell->var = NULL;
			parse_quotes(word, mshell, str, i);
			return ;
		}
	}
	mshell->var = is_in_env(mshell, ft_strndup(str + j, (*i - j)));
	if (mshell->var != NULL)
		mshell->res = ft_strjoin(mshell->res, mshell->var);
	else
	{
		free(mshell->var);
		mshell->var = NULL;
		return ;
	}
	free(mshell->var);
	mshell->var = NULL;
	return ;
}

void	parse_dollar_dquotes(int type, t_mshell *mshell, char *str, int *i)
{
	int		j;
	char	*res;

	mshell->j = i;
	(*i)++;
	if (str[*i] == 34 || str[*i] == 39)
	{
		if (str[*i] == type)
			mshell->res = ft_strjoin(mshell->res, ft_strdup("$"));
		return ;
	}
	if (str[*i] == '=')
	{
		(*i)++;
		mshell->res = ft_strjoin(mshell->res, ft_strdup("$="));
		return ;
	}
	if (str[*i] >= '0' && str[*i] <= '9')
	{
		(*i)++;
		mshell->var = is_in_env(mshell, ft_strndup(str + j, (*i - j)));
		if (mshell->var != NULL)
			mshell->res = ft_strjoin(mshell->res, mshell->var);
		else
		{
			free(mshell->var);
			mshell->var = NULL;
			return ;
		}
	}
	while (str[*i] != type && str[*i] != '\0' && str[*i] != '=')
	{
		if (str[*i - 1] == '$' && type == 34)
		{
			while (str[*i] != type && str[*i] != '\0' && str[*i] != '=')
				(*i)++;
			mshell->var = is_in_env(mshell, ft_strndup(str + mshell->j, (*i - mshell->j)));
			if (mshell->var != NULL)
				mshell->res = ft_strjoin(mshell->res, mshell->var);
			else
				mshell->res = ft_strjoin(mshell->res, ft_strdup(""));
			j = (*i);
			(*i)++;
			continue ;
		}
		(*i)++;
	}
	if (str[*i] == '=')
	{
		mshell->var = is_in_env(mshell, ft_strndup(str + *mshell->j, (*i - *mshell->j)));
		if (mshell->var != NULL)
			mshell->res = ft_strjoin(mshell->res, mshell->var);
		*mshell->j = (*i);
		return ;
	}
	if (str[*i] == '\0')
	{
		printf("quote error\n");
		return ;
	}
	if (type == 34)
	{
		mshell->var = is_in_env(mshell, ft_strndup(str + j, (*i - j)));
		if (mshell->var != NULL)
				mshell->res = ft_strjoin(mshell->res, mshell->var);
		else
			mshell->res = ft_strjoin(mshell->res, ft_strdup(""));
	}
	else if (type == 39)
	{
		mshell->res = ft_strjoin(mshell->res, mshell->var);
		(*i)++;
	}
	free(mshell->var);
	mshell->var = NULL;
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
