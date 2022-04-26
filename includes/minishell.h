/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:33:36 by amontant          #+#    #+#             */
/*   Updated: 2022/04/26 18:28:32 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <signal.h>
# include "libft.h"
# include "builtins.h"
# include <sys/types.h>
# include <sys/wait.h>

# define KEY_UP 38

struct	s_command;
struct	s_mshell;

typedef struct s_command
{
	char				**value;
	int					pipe_fd[2];
	struct s_command	*next;
}	t_command;

typedef enum e_token
{
	string = 0,
	builtin = 1,
	flag = 2,
	PIPE = 3,
	redir_in = 4,
	redir_out = 5,
	d_variable = 6,
	here_doc = 7,
	here_doc_del = 8,
	redir_app = 9,
}	t_token;

typedef struct s_split
{
	char			c;
	struct s_split	*next;
}	t_split;

typedef struct s_pipe
{
	int					pipe_fd[2];
	struct s_pipe		*next;
}	t_pipe;

typedef struct s_phrase
{
	char			*str;
	int				token;
	struct s_phrase	*next;
}	t_phrase;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_mshell
{
	t_env		*env;
	char		**path;
	t_command	*command;
	t_phrase	*phrase;
	t_split		*word;
}	t_mshell;

/**************MAIN*****************/
int			ft_read(char *str, t_mshell *mshell);
void		free_mshell(t_mshell *mshell, char *str);

/**************PARSE****************/
int			check_args(int ac, char **av);
int			parse_command(char *str, t_mshell *mshell);
t_command	*create_command(t_mshell *mshell);
int			is_delim(char *str, int *i);
int	is_redir(char *str, int *i);

/*************ENV_LIST****************/
void		print_env(t_env *env);
void		del_one(t_env **lst, t_env *to_del);
t_env		*env_new(char *name, char *value);
void		env_add_back(t_env **alst, t_env *new_elem);
void		env_free(t_env *env);

/************ENV*************************/
t_env 		*parse_env(char **env_t);

/************PARSE_VARS*******************/
void		is_in_env(t_mshell *mshell, char *str);
void		parse_dollar(t_split **word, t_mshell *mshell,
			char *str, int *i);
char		*ft_strndup(const char *s, int size);
void		parse_dollar_dquotes(t_split **word, t_mshell *mshell, char *str, int *i);
char		*ft_strndup(const char *s, int size);

/***********SPLIT*******************/
void		split_command(char *str, t_mshell *mshell);
void		make_word(t_split **word, t_mshell *mshell);
void		parse_quotes(t_split **word, t_mshell *mshell,
				char *str, int *i);
int			parse_string(t_split **word, t_mshell *mshell,
				char *str, int *i);
void		parse_delimiter(t_split **word, t_mshell *mshell,
				char *str, int *i);
void		parse_dollar(t_split **word, t_mshell *mshell,
				char *str, int *i);
/***********SPLIT_UTILS*******************/
t_split		*split_lstnew(char c);
void		split_lstadd_back(t_split **alst, t_split *new);
int			split_lstsize(t_split *lst);
void		phrase_lstadd_back(t_phrase **alst, t_phrase *new);
void		print_split(t_split **split);

/***********WORD_UTILS*******************/
void		print_phrase(t_phrase **phrase);
void		ft_wordclear(t_split **lst);
t_phrase	*phrase_lstnew(char *str);
int			phrase_lstsize(t_phrase *lst);
void		free_phrase(t_phrase **phrase);
/************COMMAND_UTILS**********/
void		command_lstadd_back(t_command **alst, t_command *new);
t_command	*command_lstnew(char **commands);
void		print_tab(char **tab);
int			count_delim(t_phrase **phrase);
void		freetab(char **tab);
void		print_command(t_command *command);
int			command_size(t_command *command);
void		free_command(t_command **command);
/**************INIT*****************/
t_mshell *init_mshell(char **env);

/**************ARM_SIGNAL************/
void armsignals(void);
void sig_handler(int signum);

/************ASSIGN_TOKENS***********/
void assign_tokens(t_mshell *mshell);
int is_variable(char *str);
int is_builtin(char *str);

/************BUILTINS*****************/
void del_one(t_env **lst, t_env *to_del);
char *get_value(char *line);
char *get_name(char *line);
void export_variable(t_env **env, char *new_v);
void ft_export(t_env **env, char **params);
int check_valid_variable(char *variable);
void check_rm_double(t_env **env);
void ft_unset(t_env **env, char **params);
void unset_variable(t_env **env, char *variable_name);
void cd(char **params);
void pwd(void);
int is_valid_opt(char *arg);
int get_opt(char **args);
void echo(char **args);


/*************EXEC*********************/
void			ft_exe(t_mshell *mini);
void			exe_builtins(char **params, t_env **env);
void			exec_cmd(t_env *env, t_command *command, t_command *current);
int				lst_env_size(t_env *env);
char			**env_to_tab(t_env *env);
char			**create_paths(t_env *env);
void			free_tab(char **tab);
char			*ft_strjoin_f(char *s1, char const *s2);
char			*find_path(t_env *env, char **cmd_params);
char			*check_absolute_path(char *path);
int				is_builtins(char **params);
int				cmd_list_size(t_command *lst);
int				cmd_lst_pos(t_command *lst, t_command *current);
void			ft_dup(t_command *command, t_command *current, int *pipe_fd, int i);
t_pipe			*set_lst_pipe(t_command *command);
void			add_back_pipe(t_pipe **pipe);
void			execute(t_env *env, t_command *command, t_command *current, int *pipe_fd, int i);
int				*set_pipe(t_command *command);
void			close_pipe_n_wait(int *pipe_fd);
void			exit_if_builtin_last(t_command *command, t_command *current);




#endif