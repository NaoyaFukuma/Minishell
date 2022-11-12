/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 01:19:07 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/10 16:38:16 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>             // for printf() perror() strerror()
# include <errno.h>             // for errno
# include <readline/history.h>  // for add_history()
# include <readline/readline.h> // for readline()
# include <stdbool.h>           // for type bool
# include <stdlib.h>            // for free()
# include <string.h>
# include <sys/stat.h> // for stat()
# include <unistd.h>   // for write(), access(), execve()
# include <sys/types.h>
# include <fcntl.h>

# define BACK_CURSOR "\e[1D"
# define CLEAR_FROM_CURSOR "\e[K"
# define UP_LINE_CURSOR "\e[A"
# define ADVANCE_CURSOR "\e[3C"

# define ENV_TRUNC 0
# define ENV_APPEND 1
# define RED_COLOR "\e[31m"
# define GREEN_COLOR "\e[32m"
# define YELLOW_COLOR "\e[33m"
# define WHITE_COLOR "\e[37m"
# define DEFAULT_COLOR "\e[m"

# define SYNTAX_ERROR		258
# define TOKEN_ERROR		2
# define CMD_NOT_FOUND		127
# define CMD_NOT_EXECUTABLE	126

# define NO_PID -1
# define PIPE_WRITE 1
# define PIPE_READ 0

# define REDIRECT_IO_NUM_ERROR -1
# define REDIRECT_UNDEFINED -1


typedef struct stat			t_stat;

typedef struct s_env
{
	char					*name;
	char					*value;
	bool					is_env;
	struct s_env			*next;
}							t_env;

/* global */
typedef struct s_shell
{
	t_env					*envs;
	int						status;
	char					*pwd;
	bool					interactive;
	bool					interrupted;
	bool					exited;
	int						prompt_len;
}							t_shell;

typedef enum	e_token_type
{
	CHAR_BACKSLASH = '\\',
	CHAR_SEMICOLON = ';',
	CHAR_QUOTE = '\'',
	CHAR_D_QUOTE = '\"',
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_LESS = '<',
	CHAR_GREATER = '>',
	CHAR_SPACE = ' ',
	CHAR_TAB = '\t',
	CHAR_NIL = '\0',
	CHAR_OPEN_PARENTHESES = '(',
	CHAR_CLOSE_PARENTHESES = ')',
	CHAR_OTHER = -1,
	TOKEN = -1,
	IO_NUMBER = -2,
	D_GREATER = -3,
	AND_OPERATER = -5,
	OR_OPERATER = -6,
}				t_token_type;

typedef enum	e_token_status
{
	QUOTED,
	D_QUOTED,
	PARENTHESESED,
	NOT_QUOTED,
}				t_token_status;

typedef struct	s_token_list	t_token_list;

struct						s_token_list
{
	t_token_list			*prev;
	t_token_list			*next;
	t_token_type			type;
	char					*comp; //component
};

typedef struct	s_token_info
{
	size_t					str_i;
	size_t					each_i;
	size_t					len;
	t_token_list			*first_token;
	t_token_list			*token;
	bool					quote_flag;
	t_token_status			status;
	bool					esc_flag;
	char					*quote_start;
}				t_token_info;

typedef enum			e_redirect_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND_OUTPUT
}						t_redirect_type;

typedef struct			s_redirect
{
	int					fd_io;
	int					fd_file;
	int					fd_backup;
	t_redirect_type		type;
	t_token_list		*filename;
	struct s_redirect	*next;
	struct s_redirect	*prev;
}						t_redirect;

typedef enum			e_logical_ope_state
{
	NO_OPE,
	AND,
	OR,
}						t_logical_ope_state;

typedef struct			s_command
{
	t_token_list		*args;
	t_redirect			*redirects;
	pid_t				pid;
	struct s_command	*next;
	t_logical_ope_state	logi_state;
	bool				subshell_flag;
}						t_command;

typedef enum			e_pipe_state
{
	NO_PIPE,
	PIPE_READ_ONLY,
	PIPE_WRITE_ONLY,
	PIPE_READ_WRITE
}						t_pipe_state;

typedef enum			e_cmd_type
{
	ABSOLUTE,
	RELATIVE,
	COMMAND
}						t_cmd_type;

typedef enum	e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_SEMICOLON,
	NODE_OPERATER
}				t_node_type;

typedef struct	s_node
{
	t_node_type		type;
	t_command		*command;
	struct s_node	*left;
	struct s_node	*right;
}				t_node;

typedef struct	s_parse_info
{
	t_command		*last_command;
}				t_parse_info;

typedef struct	s_expander
{
	size_t			str_i;
	t_token_status	status;
	t_token_type	type;
	char			*str;
}				t_expander;

// in main.c
void	run_cmdline(char *line);

// in util/util_token.c
void	delete_token(t_token_list **token_list);
void	delete_token_list(t_token_list **token_list);
t_token_list	*duplicate_token(t_token_list *token);
void	add_token_into_original(t_token_list **token, t_token_list *original);

// in lexer/lexer.c
t_token_list				*lexer(char *str, bool esc_flag);
t_token_list	*init_token(t_token_list *prev, size_t len);
t_token_type	get_token_type(char c);


// in lexer_not_in_qoute.c
void	not_in_quote_lexer(t_token_info *info, t_token_type type, char *str);


// in lexer_in_qoute.c
void	in_quote_lexer(t_token_info *info, t_token_type type, char *str);
void	in_d_quote_lexer(t_token_info *info, t_token_type type, char *str);
void	in_parentheses_lexer(t_token_info *info, t_token_type type, char *str);


// in lexer_set_fin_nullchar_and_check_token_list.c
void	set_fin_nullchar_and_check_token_list(t_token_info *info);
void	del_token_list(t_token_list **token_p);
void	del_token(t_token_list **token_p);

// in parser.c
bool	parser(t_node **parent_node, t_token_list **token);

// in parser_print.c
void	print_parser(t_command *cmd);

// in parser_util.c
void	add_token_into_cmd_args(t_token_list **cmd_args, t_token_list **token);
void	input_cmd_args(t_command *command, t_token_list **token);

// in parser_redirect_util.c
t_redirect	*create_and_init_redirect(void);
void	delete_redirect_list(t_redirect **redirect);
bool	input_redirect_type_and_fd(t_token_list *token, t_redirect *redirect);
void	input_redirect(t_redirect **dst, t_redirect *new);

/// in util/util_node.c
t_node	*create_and_init_node();
t_node	*add_parent_node(t_node *left, t_node *right);

// in utils/util_create_prompt_str.c
char	*util_create_prompt_str(void);
char	*util_join_and_free_err_exit(char *str1, bool free_str1, char *str2,
		bool free_str2);

// in signal/signal.c
void	set_sig_for_interactive_shell(void);
void	set_sig_for_cmd_running(void);
void	set_sig_for_wait_child(void);


// in utils/util_create_prompt_str.c
char	*util_create_prompt_str(void);

// in signal/signal.c
void	set_sig_for_interactive_shell(void);

// in utils/utils.c
bool						util_is_builtin(const char *arg);
bool						util_is_digit_str(const char *str);
bool						util_is_directory(const char *path);
bool						util_is_same_dir(char *dir1, char *dir2);
void	util_set_status(int status);

// in utils/util_error.c
void						util_put_cmd_err_and_exit(char *cmd);
void						util_put_cmd_err(char *command, char *message);
void						util_put_env_name_error(char *command, char *name);
void	util_put_bad_fd_error(int fd);


// in utils/util_env_list.c
t_env						*util_list_new_envnode(char *env_str);
t_env						*util_list_get_last_envnode(t_env *node_ptr);
void	util_list_add_last_new_envnode(t_env **envs,
									t_env *new_env);

// in utils/util_env.c
t_env						*util_env_get(const char *name);
void	util_env_update_value(const char *env_name,
							const char *new_value,
							bool is_env_var,
							bool append_flag);
bool						util_validate_env_name(char *name);
t_env						*util_copy_envs(t_env *envs_list);

// in utils/util_path.c
size_t						util_ptrarr_len(void **ptrarr);
void						**util_ptrarr_add_back(void **ptrarr, void *ptr);
char						*util_join_path(char *prv_path, char *nxt_path);

// in utils/util_path_canonical.c
char						*util_path_canonical(char *path);
char						**util_colon_split(char *src_str, char *def);

// in init/init_shell.c
void						init_minishell(void);
void						init_pwd(void);
void						init_oldpwd(void);

// in expander/expander.c
void	expander(t_token_list **tokens);

// in expand_env.c
char	*expand_env(char *src_str);

// in expand_env2.c
char	*set_env_name(char *str);
char	*set_env_value(char *name);
char	*create_esc_val(char *str, t_token_status state);

// in exec/exec.c
void			exec_nodes(t_node *nodes);
int	exec_cmd(t_command *cmd, t_pipe_state *pipe_state, int *old_pipe);

// in exec/redirect_util.c
bool	redirect_util_setup(t_command *cmd);
void			redirects_util_cleanup(t_command *command);
bool			redirect_util_dupfd(t_command *command, bool is_parent);

// in exec/pipe_util.c
void	pipe_util_create_new_pipe(t_pipe_state pipe_state, int new_pipe[]);
void	pipe_util_setup(t_pipe_state state, int old_pipe[], int new_pipe[]);
void	pipe_util_cleanup(t_pipe_state state, int old_pipe[], int new_pipe[]);


// in exec/args_util.c
bool		token_to_args(t_command *cmd, char ***args);

// in exec/exec_logi_ope.c
void	exec_logi_ope(t_command *cmd);


// in exec/exec_cmd.c
void	exec_cmd_child(t_command *cmd, char **args, t_pipe_state pipe_state,
		int old_pipe[]);
int		exec_cmd_parent(t_command *command, char **args);
int		exec_builtin(char **args);


// in exec/exec_external.c
void							exec_external(char **cmd_args);

// in exec/exec_external_util.c
char	*get_binary_path(char *src_path);
bool	is_executable(const char *path);
void	wait_external_cmds(t_command *cmd);

// in builtin/builtin_cd1.c
int							builtin_cd(char **args);

// in builtin/builtin_cd2.c
bool						try_change_dir(char *dst_path);
char						*get_cwd_path(char *cmd);
char						*get_new_pwd(char *path, bool flag,
								bool is_abs_path);

// in builtin/builtin_cd3.c
void						bind_pwd_value(void);
char	*try_splitted_cdpath(char **split_cd, char *dst_dir);

// in builtin/builtin_echo.c
int							builtin_echo(char **args);

// in builtin/builtin_env.c
int							builtin_env(void);

// in builtin/builtin_exit.c
int							builtin_exit(char **args);

// in builtin/builtin_export.c
int							builtin_export(char **args);

// in builtin/builtin_export_sort.c
void						env_sort_for_export(t_env **lst);

// in builtin/builtin_expor_print.c
int							print_each_envs(void);

// in builtin/builtin_pwd.c
int							builtin_pwd(void);

// in builtin/builtin_unset.c
int							builtin_unset(char **args);


#endif
