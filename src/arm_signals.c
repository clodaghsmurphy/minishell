/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arm_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:20:52 by clmurphy          #+#    #+#             */
/*   Updated: 2022/04/13 15:04:37 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("^C\n");
		exit(0);
	}
}

void	armsignals(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sig_handler;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}
