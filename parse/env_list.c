/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiloub <shiloub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:27:45 by amontant          #+#    #+#             */
/*   Updated: 2022/04/14 18:56:09 by shiloub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_add_back(t_env **alst, t_env *new_elem)
{
	t_env	*current;

	if (!alst || *alst == NULL)
	{
		*alst = new_elem;
		return ;
	}
	current = *alst;
	if (!new_elem)
		return ;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new_elem;
}

t_env	*env_new(char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	env_free(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		free(env->name);
		free(env->value);
		temp = env;
		env = env->next;
		free(temp);
	}
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
