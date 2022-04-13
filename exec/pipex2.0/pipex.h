/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:19:44 by amontant          #+#    #+#             */
/*   Updated: 2022/04/13 14:13:52 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_process
{
	int		infile_fd;
	int		outfile_fd;
	char	**cmd_params_1;
	char	*path_1;
	char	**cmd_params_2;
	char	*path_2;
	
	int		pipe_fd[2];
}	t_process;

char		**create_paths(char **env);
char		*ft_strdup(const char *s);
char		*find_path(char *cmd, char **env, char ***cmd_params, t_process *p);
void		exec_cmd_1(char **av, char **env, t_process *process);
void		exec_cmd_2(char **av, char **env, t_process *process);
char		*ft_strjoin_f(char *s1, char const *s2);
void		error(char *str);
void		free_tab(char **tab);
char		*check_absolute_path(char *path);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strlen(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		free_to_exit(char **paths, t_process *p);
void		error_path_fd(int fd, char *path, char **cmd_params, char *cmd);
void		error_path_fd_1(t_process *process, char *infile_name);
void		error_path_fd_2(t_process *process, char *outfile_name);
void		free_process(t_process *process);
t_process	*set_process(char **av, char **env);
void		init_process(t_process *process);

#endif