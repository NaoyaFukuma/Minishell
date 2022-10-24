/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:31:10 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/24 00:50:34 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

/* environ node struct*/
typedef struct s_env
{
	char			*name;
	char			*value;
	bool			is_env;
	struct s_env	*next;
}				t_env;

#define	ENV_TRUNC 0
#define	ENV_APPEND 0

// in utils/utils.c
bool	util_is_builtin(const char *arg);
bool	util_is_digit_str(const char *str);

// in utils/util_error.c
void	util_perror_and_exit(char *cmd);
void	util_put_cmd_err(char *command, char *message);

// in utils/util_env_list.c
t_env	*util_list_new_envnode(char *env_str);
t_env	*util_list_get_last_envnode(t_env *node_ptr);
void	util_list_add_last_new_envnode(t_env **envs,
									t_env *new_env);

// in util/util_env.c
t_env	*util_env_get(const char *name);
void	*util_env_set(const char *name);

#endif
