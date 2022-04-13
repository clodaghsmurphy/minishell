/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:15:52 by amontant          #+#    #+#             */
/*   Updated: 2022/04/13 14:56:42 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

void	del_one(t_env **lst, t_env *to_del);
char	*get_value(char *line);
char	*get_name(char *line);
t_env	*env_new(char *name, char *value);
void	env_add_back(t_env **alst, t_env *new_elem);
void	env_free(t_env *env);
void	export_variable(t_env **env, char *new_v);
void	ft_export(t_env **env, char **params);
int		check_valid_variable(char *variable);
void	print_env(t_env *env);
void	del_one(t_env **lst, t_env *to_del);
void	check_rm_double(t_env **env);
void	ft_unset(t_env	**env, char **params);
void	unset_variable(t_env **env, char *variable_name);
void	cd(char *path);
void	pwd(void);
int		is_valid_opt(char *arg);
int		get_opt(char **args);

#endif