/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:31:10 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/30 15:02:44 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include <errno.h>             // for errno
# include <readline/history.h>  // for add_history()
# include <readline/readline.h> // for readline()
# include <stdbool.h>           // for type bool
# include <stdio.h>             // for printf() perror() strerror()
# include <stdlib.h>            // for free()
# include <sys/stat.h>          // for stat()
# include <unistd.h>            // for write(), access(), execve()

/* environ node struct*/
typedef struct s_env
{
	char			*name;
	char			*value;
	bool			is_env;
	struct s_env	*next;
}					t_env;

# define ENV_TRUNC 0
# define ENV_APPEND 1

# define RED_COLOR "\e[31m"
# define DEFAULT_COLOR "\e[m"

// in utils.c
bool				util_is_builtin(const char *arg);
bool				util_is_digit_str(const char *str);
bool				util_is_directory(const char *path);
bool				util_is_same_dir(char *dir1, char *dir2);

// in util_error.c
void				util_put_cmd_err_and_exit(char *cmd);
void				util_put_cmd_err(char *command, char *message);

// in util_env_list.c
t_env				*util_list_new_envnode(char *env_str);
t_env				*util_list_get_last_envnode(t_env *node_ptr);
void	util_list_add_last_new_envnode(t_env **envs,
									t_env *new_env);

// in util_env.c
t_env				*util_env_get(const char *name);
void				util_env_set(const char *target_name, const char *value,
						bool is_env, int mode);
void	util_env_update_value(const char *env_name,
							const char *new_value,
							bool is_env_var,
							bool append_flag);

// in util_path.c
size_t				util_ptrarr_len(void **ptrarr);
void				**util_ptrarr_add_back(void **ptrarr, void *ptr);
char				*util_join_path(char *prv_path, char *nxt_path);

// in util_path_canonical.c
char				*util_path_canonical(char *path);
char				**util_colon_split(char *src_str, char *def);

#endif
