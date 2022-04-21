/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiloub <shiloub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:17:23 by amontant          #+#    #+#             */
/*   Updated: 2022/04/21 19:57:05 by shiloub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char **params)
{
	char	*error;

	if (!params[1])
		return ;
	if (params[2])
	{
		ft_putstr_fd("cd : too much arguments\n", 2);
		return;
	}
	error = ft_strjoin("cd: ", params[1]);
	if (chdir(params[1]) != 0)
		perror(error);
}

void	pwd(void)
{
	char	wd[10000];

	getcwd(wd, 10000);
	ft_putstr_fd(wd, 1);
	ft_putchar_fd('\n', 1);
}
