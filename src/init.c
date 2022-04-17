/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:26:06 by clmurphy          #+#    #+#             */
/*   Updated: 2022/04/17 18:59:37 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell	*init_mshell(char **env)
{
	t_mshell	*mshell;

	armsignals();
	mshell = ft_calloc(sizeof(t_mshell), 1);
	if (!mshell)
		return (NULL);
	mshell->env = parse_env(env);
	return (mshell);
}
