/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:41:42 by amontant          #+#    #+#             */
/*   Updated: 2022/04/05 18:43:59 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_value(char *line);
char	*get_name(char *line);
t_env	*env_new(char *name, char *value);
void	env_add_back(t_env **alst, t_env *new);
void	env_free(t_env *env);

t_env	*parse_env(char **env_t)
{
	int		i;
	t_env	*env;

	env = NULL;
	i = 0;
	while (env_t[i])
	{
		env_add_back(&env, env_new(get_name(env_t[i]), get_value(env_t[i])));
		i++;
	}
	return (env);
}

char	*get_name(char *line)
{	
	int		i;
	char	*name;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	name = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (line[i] && line[i] != '=')
	{
		name[i] = line[i];
		i++;
	}
	name[i] = 0;
	return (name);
}

char	*get_value(char *line)
{	
	int		i;
	int		count;
	char	*value;

	i = 0;
	count = 0;
	while (line[i] && line[i] != '=')
		i++;
	while (line[i + count])
		count ++;
	value = malloc(sizeof(char) * (count));
	count = 0;
	i++;
	while (line[i])
	{
		value[count] = line[i];
		i++;
		count ++;
	}
	value[count] = 0;
	return (value);
}

void	print_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		ft_putstr_fd(current->name, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(current->value, 1);
		ft_putstr_fd("\n", 1);
		current = current->next;
	}
}

int	main(int ac, char **av, char **env)
{
	char	*s1;
	char	*s2;
	t_env	*salam;

	salam = parse_env(env);
	print_env(salam);
	env_free(salam);
	return 0;
}

void	export_variable(t_env *env, char *new_v)
{
	
}