//**************************cmd_list_utils.c********************************

int	cmd_list_size(t_command *lst);
int	cmd_lst_pos(t_command *lst, t_command *current);


//**************************decla.c********************************

int	cmd_list_size(t_command *lst);
int	cmd_lst_pos(t_command *lst, t_command *current);


//**************************exec.c********************************

void	ft_exe(t_mshell *mini);
void	delete_hd(t_command *command);
void	exec_cmd(t_mshell *mini);
void	exe_child_daron(t_mshell *mini, t_command *cur, int i, int pid);
void	get_last_retour_builtin(t_command *lst, t_mshell *mini);
void	execute(t_mshell *mini, t_command *current, int i);
void	ft_dup(t_mshell *mini, t_command *current, int i);
void	dup_redir_in_out(t_command *current, t_mshell *mini);
void	error(char *str, t_mshell *mini, int erreur);
void	exe_child_daron(t_mshell *mini, t_command *cur, int i, int pid);
void	execute(t_mshell *mini, t_command *current, int i);
void	ft_dup(t_mshell *mini, t_command *current, int i);
int	make_redir_out(t_command *command, t_mshell *mini);
int	make_redir_in(t_command *command, t_mshell *mini);
void	error(char *str, t_mshell *mini, int erreur);
void	error(char *str, t_mshell *mini, int erreur);


//**************************exec_utils2.c********************************

void	exit_if_builtin_only(t_mshell *mini, t_command *current);
void	close_pipe_n_wait(int *pipe_fd, int *pids);
void	close_pipe_n_wait(int *pipe_fd, int *pids);
int	*set_pipe(t_command *command);


//**************************exec_utils.c********************************

void	exe_builtins(char **params, t_env **env, t_mshell *mini);
int	simul_exe_builtins(char **params, t_mshell *mini);
int	is_builtins(char **params);
int	lst_env_size(t_env *env);
void	exe_builtins(char **params, t_env **env, t_mshell *mini);
int	simul_exe_builtins(char **params, t_mshell *mini);
int	is_builtins(char **params);
char	**env_to_tab(t_env *env);


//**************************free.c********************************

void	free_redir_in(t_redir_in *lst);
void	free_redir_out(t_redir_out *lst);
void	free_mini(t_mshell *mini);


//**************************heredoc.c********************************

void	replace_heredoc(t_redir_in *to_change, char *hd_name);
char	*get_hd_name(void);
void	find_replace_hd(t_redir_in *lst);
void	heredoc(t_mshell *mini, char *name, char *stop);
int	launch_hd(t_mshell *mini);
void	replace_heredoc(t_redir_in *to_change, char *hd_name);
char	*get_hd_name(void);
void	heredoc(t_mshell *mini, char *name, char *stop);


//**************************pipe_lst.c********************************


//**************************redir_in.c********************************

void	add_back_redir_in(t_redir_in **lst, char *file_name, int bol);
void	add_back_redir_in(t_redir_in **lst, char *file_name, int bol);
t_redir_in	*parse_redir_in(char **command);
void	add_back_redir_in(t_redir_in **lst, char *file_name, int bol);
char	**command_clear_all_in(char **command);
char	**command_clear_one_in(char **command);
t_redir_in	*parse_redir_in(char **command);


//**************************redir_out.c********************************

void	add_back_redir_out(t_redir_out **lst, char *file_name, int	bol);
int		lataille(char **command);
void	add_back_redir_out(t_redir_out **lst, char *file_name, int	bol);
t_redir_out	*parse_redir_out(char **command);
char	**ft_dup_tab(char **command);
char	**command_clear_all_out(char **command);
char	**command_clear_one(char **command);
int		lataille(char **command);
void	add_back_redir_out(t_redir_out **lst, char *file_name, int	bol);
t_redir_out	*parse_redir_out(char **command);


//**************************test.c********************************

void   ft_fork(char *str);
int main();
void   ft_fork(char *str);


//**************************utils.c********************************

void	free_tab(char **tab);
char	**create_paths(t_env *env);
void	free_tab(char **tab);
char	*ft_strjoin_f(char *s1, char const *s2);
char	*find_path(t_env *env, char **cmd_params);
char	*check_absolute_path(char *path);


