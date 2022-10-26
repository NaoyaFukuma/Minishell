/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:27:08 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/26 14:13:38 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include <string.h>w

int		builtin_exit(char **args);
int		builtin_echo(char **args);
int		builtin_env(void);
bool	try_change_dir(char dst_path);
int		cd_process(char *cd_path, char *arg, bool flag);
char	*set_cd_path(const char *arg, bool *is_canon_path);
char	*get_cwd_path(char *cmd);
char	*get_new_pwd(char *path, bool flag, bool is_abs_path);
void	bind_pwd_value(void);

#endif
