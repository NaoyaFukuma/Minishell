/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 01:19:07 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/26 16:39:20 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>             // for printf() perror() strerror()
# include <errno.h>             // for errno
# include <readline/history.h>  // for add_history()
# include <readline/readline.h> // for readline()
# include <stdbool.h>           // for type bool
# include <stdlib.h>            // for free()
# include <unistd.h>            // for write(), access(), execve()
# include <sys/stat.h> // for stat()
# include <string.h>
# include "libft.h"

// # define RED_COLOR "\e[31m"
// # define WHITE_COLOR "\e[m"
# define BACK_CURSOR "\033[2D"
# define CLEAR_FROM_CURSOR "\033[0K"

#define	ENV_TRUNC 0
#define	ENV_APPEND 1

# define RED_COLOR "\e[31m"
# define WHITE_COLOR "\e[m"

typedef struct stat	t_stat;

typedef struct s_env
{
	char			*name;
	char			*value;
	bool			is_env;
	struct s_env	*next;
}				t_env;


/* global */
typedef struct s_shell
{
	t_env			*envs;
	int				status;
	char			*pwd;
	bool			interactive;
	bool			interrupted;
	bool			exited;
}					t_shell;

// in utils.c
bool	util_is_builtin(const char *arg);
bool	util_is_digit_str(const char *str);
bool	is_directory(const char *path);

// in util_error.c
void	util_put_cmd_err_and_exit(char *cmd);
void	util_put_cmd_err(char *command, char *message);

// in util_env_list.c
t_env	*util_list_new_envnode(char *env_str);
t_env	*util_list_get_last_envnode(t_env *node_ptr);
void	util_list_add_last_new_envnode(t_env **envs,
									t_env *new_env);

// in util_env.c
t_env	*util_env_get(const char *name);
void	util_env_set(const char *target_name, const char *value, bool is_env,int mode);
int		util_envs_print(t_env *envs);
void		util_env_update_value(const char *env_name, const char *new_value, bool is_env_var, bool append_flag);

// in util_path.c
size_t	util_ptrarr_len(void **ptrarr);
void	**util_ptrarr_add_back(void **ptrarr, void *ptr);
char	*util_join_path(char *prv_path, char *nxt_path);

// in path_canonical.c
char	*path_canonical(char *path);
char	**util_colon_split(char *src_str, char *def);


typedef enum	e_token_type
{
	CHAR_BACKSLASH = '\\',
	CHAR_SEMICOLON = ';',
	CHAR_QUOTE = '\'',
	CHAR_D_QUOTE = '\"',
	CHAR_PIPE = '|',
	CHAR_LESS = '<',
	CHAR_GREATER = '>',
	CHAR_SPACE = ' ',
	CHAR_TAB = '\t',
	CHAR_OTHER,
}				t_token_type;

typedef enum	e_token_status
{
	QUOTED,
	D_QUOTED,
	NOT_QUOTED,
}				t_token_status;

typedef struct	s_token_list	t_token_list;

struct	s_token_list
{
	t_token_list	*prev;
	t_token_list	*next;
	t_token_type	type;
	char 			*comp; //component
};

typedef struct	s_token_info
{
	size_t			str_i;
	//それぞれのトークンのindex
	size_t			each_i;
	size_t			len;
	t_token_list	*first_token;
	t_token_list	*token;
	bool			quote_flag;
	t_token_status	status;
}				t_token_info;

t_token_list	*lexer(char *str);

// in init_shell.c
void				init_minishell(void);

// in exec_builtin.c
int		exec_builtin(char **args);

int	builtin_cd(char **args);
int	builtin_pwd(void);
int	builtin_unset(char **args);


int		builtin_exit(char **args);
int		builtin_echo(char **args);
int		builtin_env(void);
bool	try_change_dir(char *dst_path);
int		cd_process(char *cd_path, char *arg, bool flag);
char	*set_cd_path(char *arg, bool *is_canon_path);
char	*get_cwd_path(char *cmd);
char	*get_new_pwd(char *path, bool flag, bool is_abs_path);
void	bind_pwd_value(void);


#endif
