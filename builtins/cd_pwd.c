/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:17:23 by amontant          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/04/13 14:56:03 by clmurphy         ###   ########.fr       */
=======
/*   Updated: 2022/04/13 14:48:22 by amontant         ###   ########.fr       */
>>>>>>> 9f7997886c58acfb8134be2c62903f7c9511f487
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
