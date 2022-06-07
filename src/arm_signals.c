/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arm_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:20:52 by clmurphy          #+#    #+#             */
/*   Updated: 2022/06/04 12:08:13 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		g_estatus = 130;
		rl_on_new_line();
		rl_redisplay();
	}
}

void	armsignals(void)
{
	struct sigaction	sa;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = (void *)sig_handler;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	end_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSTOP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	signal_def(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGSTOP, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
