/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiloub <shiloub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:41:42 by amontant          #+#    #+#             */
/*   Updated: 2022/04/07 19:42:17 by shiloub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	main(int ac, char **av, char **env)
{
	char	*s1;
	char	*s2;
	t_env	*salam;

	salam = parse_env(env);
	//print_env(salam);
	export(&salam, av);
	print_env(salam);
	env_free(salam);
	return 0;
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

int	check_valid_variable(char *variable)
{
	int	i;
	i = 0;
	while (variable[i])
	{
		i++;
		if (variable[i] == '=')
			return(1);
	}
	return (0);
}

void	check_rm_double(t_env **env)
{
	t_env	*i;
	t_env	*j;
	t_env	*save;

	i = *env;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (!ft_strncmp(i->name, j->name, ft_strlen(i->name) + 1))
			{
				printf("trouvé\n");
				save = i;
				i = i->next;
				del_one(env, save);
				//break;
			}
			j = j->next;
		}
		i = i->next;
	}
}

void	del_one(t_env **lst, t_env *to_del)
{
	t_env	*current;
	t_env	*save;

	current = *lst;
	while (current->next != to_del)
		current = current->next;
	free(current->next->name);
	free(current->next->value);
	save = current->next;
	current->next = current->next->next;
	free(to_del);
}

// int	main(int ac, char **av, char **env)
// {
	// char	*s1;
	// char	*s2;
	// t_env	*salam;
	// t_env	*current;
	// t_env	*save;

	// salam = NULL;
	// env_add_back(&salam, env_new(ft_strdup("salut"), ft_strdup("slt")));
	// env_add_back(&salam, env_new(ft_strdup("achille"), ft_strdup("salut")));
	// env_add_back(&salam, env_new(ft_strdup("eric"), ft_strdup("salut")));
	// env_add_back(&salam, env_new(ft_strdup("patrick"), ft_strdup("salut")));
	// env_add_back(&salam, env_new(ft_strdup("seliset"), ft_strdup("salut")));
	// env_add_back(&salam, env_new(ft_strdup("cash"), ft_strdup("salut"))); 
	// env_add_back(&salam, env_new(ft_strdup("salut"), ft_strdup("salut")));
	// print_env(salam);
	// current = salam;
	// while (current)
	// {
	// 	if (!ft_strncmp(current->name, "cash", 1000))
	// 	{
	// 		save = current;
	// 		current = current->next;
	// 		del_one(&salam, save);
	// 	}
	// 	current = current->next;
	// }
	// print_env(salam);
	// env_free(salam);
	// return 0;
// 	int i;
// 	int j;

// 	i = j = 0;
// 	while (i < 10)
// 	{
// 		j = 0;
// 		while (j < 10)
// 		{
// 			if (j == 3)
// 				break;
// 			printf("i = %d j = %d\n",i,j);
// 			j++;
// 		}
// 		i++;
// 	}
// }