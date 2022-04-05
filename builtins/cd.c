/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:17:23 by amontant          #+#    #+#             */
/*   Updated: 2022/04/04 17:50:32 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>

void	cd(char *path)
{
	char	*error;

	error = ft_strjoin("cd: ", path);
	if (path == NULL)
		return ;
	if (chdir(path) != 0)
		perror(error);
}

void	pwd(void)
{
	char	wd[10000];

	getcwd(wd, 10000);
	ft_putstr_fd(wd, 1);
	ft_putchar_fd('\n', 1);
}

int main(int ac, char **av)
{
	cd(av[1]);
	pwd();
	return 0;
}
