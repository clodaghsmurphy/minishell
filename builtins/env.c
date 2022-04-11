/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiloub <shiloub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:41:42 by amontant          #+#    #+#             */
/*   Updated: 2022/04/08 17:29:22 by shiloub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	del_one(t_env **lst, t_env *to_del);
char	*get_value(char *line);
char	*get_name(char *line);
t_env	*env_new(char *name, char *value);
void	env_add_back(t_env **alst, t_env *new);
void	env_free(t_env *env);
void	export_variable(t_env **env, char *new_v);
void	export(t_env	**env, char **params);
int		check_valid_variable(char *variable);
void	print_env(t_env *env);
void	del_one(t_env **lst, t_env *to_del);
void	check_rm_double(t_env **env);
void	unset(t_env	**env, char **params);
void	unset_variable(t_env **env, char *variable_name);


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

void	export(t_env	**env, char **params)
{
	int	i;

	i = 1;
	if (params[i] == NULL)
		print_env(*env);
	else
	{
		while (params[i])
		{
			export_variable(env, params[i]);
			check_rm_double(env);
			i++;
		}
	}
}

void	export_variable(t_env **env, char *new_v)
{
	char	*name;
	char	*value;

	if (!check_valid_variable(new_v))
		return ;
	name = get_name(new_v);
	value = get_value(new_v);
	env_add_back(env, env_new(name, value));
}

int	main(int ac, char **av, char **env)
{
	char	*s1;
	char	*s2;
	t_env	*salam;

	salam = parse_env(env);
	unset(&salam, av);
	print_env(salam);
	env_free(salam);
	return 0;
}
