/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:19:35 by amontant          #+#    #+#             */
/*   Updated: 2022/06/04 12:21:55 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**create_paths(t_env *env)
{
	char	**paths;
	t_env	*current;

	current = env;
	while (current && ft_strncmp(current->name, "PATH", 5) != 0)
		current = current->next;
	if (current == NULL)
		return (NULL);
	paths = ft_split(current->value, ':');
	return (paths);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*ft_strjoin_f(char *s1, char const *s2)
{
	int		lens1;
	char	*strcat;
	int		i;

	lens1 = ft_strlen((char *)s1);
	i = 0;
	strcat = malloc(sizeof(char) * (lens1 + ft_strlen((char *)s2) + 1));
	if (!strcat)
		return (0);
	while (s1[i])
	{
		strcat[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		strcat[i + lens1] = s2[i];
		i++;
	}
	strcat[i + lens1] = '\0';
	free(s1);
	return (strcat);
}

char	*find_path(t_env *env, char **cmd_params)
{
	char	*path;
	char	**paths;
	int		i;
	int		find;

	paths = create_paths(env);
	i = -1;
	find = 0;
	path = NULL;
	while (paths && paths[++i] && !find)
	{
		free(path);
		paths[i] = ft_strjoin_f(paths[i], "/");
		path = ft_strjoin(paths[i], cmd_params[0]);
		if (access(path, X_OK) == 0)
			find = 1;
	}
	free_tab(paths);
	if (find)
		return (path);
	free(path);
	return (check_absolute_path(cmd_params[0]));
}

char	*check_absolute_path(char *path)
{
	if (access(path, X_OK) == 0)
		return (ft_strdup(path));
	else
		return (NULL);
}
