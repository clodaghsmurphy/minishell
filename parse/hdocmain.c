/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdocmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:46:29 by clmurphy          #+#    #+#             */
/*   Updated: 2022/06/01 11:50:08 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char	**env)
{
	t_mshell	*mshell;
	char		*str;

	mshell = init_mshell(env);
	str = hdoc_expand(str, mshell);
	printf("%s\n", str);
}
