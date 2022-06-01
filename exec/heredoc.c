/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 12:27:24 by amontant          #+#    #+#             */
/*   Updated: 2022/06/01 13:49:18 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_heredoc(t_redir_in *to_change, char *hd_name)
{
	to_change->stop = ft_strjoin(to_change->name, "\n");
	free(to_change->name);
	to_change->name = ft_strdup(hd_name);
	to_change->type = 0;
}

char	*get_hd_name(void)
{
	char	*hd;
	int		i;
	char	*base;
	char	*temp;

	i = 0;
	base = ft_strdup(".hd");
	hd = ft_strdup(base);
	while (!access(hd, F_OK) && i < 300)
	{
		free(hd);
		temp = ft_itoa(i);
		hd = ft_strjoin(base, temp);
		free(temp);
		i++;
	}
	free(base);
	if (access(hd, F_OK))
		return (hd);
	free(hd);
	return (NULL);
}

void	find_replace_hd(t_redir_in *lst)
{
	t_redir_in	*current;
	char		*str;
	int			hd_fd;

	current = lst;
	while (current)
	{
		if (current->type == 1)
		{
			str = get_hd_name();
			replace_heredoc(current, str);
			hd_fd = open(str, O_CREAT, 0666);
			close(hd_fd);
			free(str);
		}
		current = current->next;
	}
}

int	launch_hd(t_mshell *mini)
{
	t_command	*current;
	t_redir_in	*temp;
	int			pid;
	int			retour;

	end_signals();
	pid = fork();
	current = mini->command;
	if (pid == 0)
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
	waitpid(-1, &retour, 0);
	if (WIFSIGNALED(retour))
		return (1);
	return (0);
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
		free(str);
	}
	ft_putstr_fd("fin de heredoc = ctrl-d\n", 1);
	close(fd);
}
