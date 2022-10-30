/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 01:19:07 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/28 15:10:44 by nfukuma          ###   ########.fr       */
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

# define BACK_CURSOR "\e[2D"
# define CLEAR_FROM_CURSOR "\e[K"
# define UP_LINE_CURSOR "\e[A"
# define ADVANCE_CURSOR "\e[6C"

# define ENV_TRUNC 0
# define ENV_APPEND 1
# define RED_COLOR "\e[31m"
# define DEFAULT_COLOR "\e[m"

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
}							t_shell;

typedef enum e_token_type
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
	CHAR_NIL = '\0',
	CHAR_OTHER,
}							t_token_type;

typedef enum e_token_status
{
	QUOTED,
	D_QUOTED,
	NOT_QUOTED,
}							t_token_status;

typedef struct s_token_list	t_token_list;

struct						s_token_list
{
	t_token_list			*prev;
	t_token_list			*next;
	t_token_type			type;
	char					*comp; //component
};

typedef struct s_token_info
{
	size_t					str_i;
	//それぞれのトークンのindex
	size_t					each_i;
	size_t					len;
	t_token_list			*first_token;
	t_token_list			*token;
	bool					quote_flag;
	t_token_status			status;
}							t_token_info;

t_token_list				*lexer(char *str);


// in utils/utils.c
bool						util_is_builtin(const char *arg);
bool						util_is_digit_str(const char *str);
bool						util_is_directory(const char *path);
bool						util_is_directory(const char *path);
bool						util_is_same_dir(char *dir1, char *dir2);

// in utils/util_error.c
void						util_put_cmd_err_and_exit(char *cmd);
void						util_put_cmd_err(char *command, char *message);
void						util_put_env_name_error(char *command, char *name);

// in utils/util_env_list.c
t_env						*util_list_new_envnode(char *env_str);
t_env						*util_list_get_last_envnode(t_env *node_ptr);
void	util_list_add_last_new_envnode(t_env **envs,
									t_env *new_env);

// in utils/util_env.c
t_env						*util_env_get(const char *name);
void						util_env_update_value(const char *env_name,
								const char *new_value, bool is_env_var,
								bool append_flag);
bool						util_validate_env_name(char *name);
t_env						*util_copy_envs(t_env *envs_list);

// in utils/util_path.c
size_t						util_ptrarr_len(void **ptrarr);
void						**util_ptrarr_add_back(void **ptrarr, void *ptr);
char						*util_join_path(char *prv_path, char *nxt_path);

// in utils/util_path_canonical.c
char						*path_canonical(char *path);
char						**util_colon_split(char *src_str, char *def);

// in init/init_shell.c
void						init_minishell(void);
void						init_pwd(void);
void						init_oldpwd(void);

// in exec/exec_builtin.c
int							exec_builtin(char **args);

// in builtin
int							builtin_cd(char **args);
int							builtin_pwd(void);
int							builtin_unset(char **args);
int							builtin_exit(char **args);
int							builtin_echo(char **args);
int							builtin_env(void);
bool						try_change_dir(char *dst_path);
int							cd_process(char *cd_path, char *arg, bool flag);
char						*set_cd_path(char *arg, bool *is_canon_path);
char						*get_cwd_path(char *cmd);
char						*get_new_pwd(char *path, bool flag,
								bool is_abs_path);
void						bind_pwd_value(void);
int							builtin_export(char **args);
void						env_mergesort(t_env **lst, int (*cmp)());
int							export_print_envs(void);

#endif
