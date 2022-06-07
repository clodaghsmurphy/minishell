/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 12:27:24 by amontant          #+#    #+#             */
/*   Updated: 2022/06/04 12:23:04 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	launch_hd(t_mshell *mini)
{
	t_command	*current;
	t_redir_in	*temp;
	int			pid;
	int			retour;

	temp = NULL;
	end_signals();
	pid = fork();
	current = mini->command;
	if (pid == 0)
		jsuisbourre(current, temp, mini);
	waitpid(-1, &retour, 0);
	if (WIFSIGNALED(retour))
		return (1);
	return (0);
}

void	jsuisbourre(t_command *current, t_redir_in *temp, t_mshell *mini)
{
	signal_def();
	while (current)
	{
		temp = current->in;
		while (temp)
		{
			if (temp->stop)
				heredoc(mini, temp->name, temp->stop);
			temp = temp->next;
		}
		current = current->next;
	}
	free_mini(mini);
	exit(0);
}

void	heredoc(t_mshell *mini, char *name, char *stop)
{
	int		fd;
	char	*str;

	fd = open(name, O_WRONLY);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		str = get_next_line(0);
		if (!str)
			break ;
		if (!ft_strncmp(str, stop, ft_strlen(stop) + 1))
		{
			free(str);
			close(fd);
			return ;
		}
		str = hdoc_expand(str, mini);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	ft_putstr_fd("bash: warning: here-document delimited by end-of-file\n", 1);
	close(fd);
}
