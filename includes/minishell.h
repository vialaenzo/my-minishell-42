/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:29:48 by eviala            #+#    #+#             */
/*   Updated: 2024/09/25 17:04:33 by dtrala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAGENTA "\033[0;35m"
# define YELLOW_B "\033[1;93m"
# define RESET "\033[0m"

typedef enum e_type
{
	INPUT = 1,
	HEREDOC,
	TRUNC,
	APPEND,
	PIPE,
	CMD,
	ARG,
}					t_type;

extern int			g_signal;

typedef struct s_cmd
{
	bool			skip_cmd;
	int				infile;
	int				outfile;
	char			**cmd_param;
	char			*path;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_liste
{
	char			*str;
	struct s_liste	*prev;
	struct s_liste	*next;
}					t_liste;

typedef struct s_token
{
	char			*str;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_data
{
	t_liste			*env;
	t_liste			*export;
	t_token			*token;
	t_cmd			*cmd;
	char			*path;
	int				exit_code;
	int				last_pid;
	int				pipe[2];
}					t_data;

// parsing/verif_quotes.c
void				which_quote(bool *dq, bool *sq, int *index, char c);
int					verif_quotes(t_data *data, char *line);

// utils/ft_tokens.c
size_t				ft_token_size(t_token **list);
t_token				*ft_token_new(char *str, t_type type);
int					ft_token_add_back(t_token **list, t_token *token);
void				ft_token_clear(t_token **list);
t_token				*ft_token_last(t_token **list);

// parsing/make_tokens.c
bool				make_tokens(t_token **begin, char *line);

// utils/ft_cmds.c
void				ft_cmd_clear(t_cmd **list);
t_cmd				*ft_cmd_last(t_cmd **list);
t_cmd				*ft_cmd_new(int infile, int outfile, char **cmd_param);
int					ft_cmd_add_back(t_cmd **list, t_cmd *cmd);
void				ft_cmd_clear(t_cmd **list);

// utils/ft_cmds2.c
size_t				ft_cmd_size(t_cmd **cmd);

// parsing/make_cmds.c and ft_cmds_ars.c
bool				make_cmds(t_data *data);
char				**get_param(t_data *data, t_token *token);

// parsing/fd_center.c
bool				get_outfile(t_token *token, t_cmd *cmd);
bool				get_infile(t_data *data, t_token *token, t_cmd *cmd);

// utils/ft_lists.c
size_t				ft_liste_size(t_liste **list);
void				ft_liste_clear(t_liste **list);
int					ft_liste_add_back(t_liste **list, t_liste *liste);
t_liste				*ft_liste_new(char *str);

// utils/utils.c
bool				ft_error(char *str);
bool				is_space(char c);
int					is_special(char *str);
bool				invalid_line(char *line);
bool				check_is_pipe(t_data *data);

// utils/utils2.c
bool				error_token(t_token *token);
int					ft_str_add_chr(char **str, char c);
int					ft_size_tab(char **tab);
bool				verif_special(t_data *data);

// utils/ft_env.c
int					ft_env_get(char *key, char **value, t_liste *env);
int					ft_env_new(t_data *data);
int					ft_env_sort(t_liste **env);
int					ft_env_to_tab(t_liste **env, char ***tab);
int					ft_env_has(char *key, t_liste *env);

// parsing/expand.c
int					ft_expand(char **line, t_data *data);

// builtins/*.c
int					ft_cd(t_data *data, char **args);
int					ft_echo(char **args);
int					ft_env(t_liste **env, char *prefix);
int					ft_export(t_data *data, char **args);
int					ft_check_key(char *key);
int					ft_export_one(t_liste **env, t_liste **export, char *str);
int					ft_export_one_append(t_liste **env, t_liste **export,
						char *str);
int					ft_pwd(char **args);
int					ft_unset(t_data *data, char **args);
int					ft_unset_one(t_liste **env, char *var);
void				ft_exit(t_data *data, char **args);

// ft_free.c
void				free_everything(t_data *data, char *err, int ext);
void				free_everything_heredoc(t_data *data, char *err, int ext);

// exec/here_doc
int					here_doc(t_data *data, char *limiter);

// exec/exec.c
bool				exec(t_data *data);

// exec/builtins_starter.c
bool				builtins_starter(t_data *data, t_cmd *cmd);

// exec/utils.c
bool				is_builtin(char *cmd, char *TYPE);
void				wait_all(t_data *data);

// exec/childs.c
void				child_process(t_data *data, t_cmd *cmd, int *pipe_fds);
int					ft_export_last_arg(t_data *data);

// exec/exec_cmds.c
bool				is_cmd(t_data *data, t_cmd *cmd);

// exec/exec_cmds2.c
char				*cmd_finder(t_data *data, t_cmd *cmd, t_liste *env);

// utils/ft_signals
void				handle_sigint_exec(int i);
void				signals(void);
void				signals_quit(void);

// Tests Debug
bool				test_token(t_data *data, char *line);
void				token_display(t_token *token);
void				cmd_display(t_cmd *cmd);
bool				test_cmds(t_data *data);
#endif
