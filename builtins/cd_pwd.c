/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:17:23 by amontant          #+#    #+#             */
/*   Updated: 2022/04/13 14:48:22 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>

void	cd(char **params)
{
	char	*error;

	if (!params[1])
		return ;
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
