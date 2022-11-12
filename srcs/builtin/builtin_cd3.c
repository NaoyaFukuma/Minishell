/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:54:11 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/13 01:44:59 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bind_pwd_value(void)
{
	extern t_shell	g_shell;

	util_env_update_value("OLDPWD", util_env_get("PWD")->value, false, false);
	util_env_update_value("PWD", g_shell.pwd, false, false);
}

char	*get_cwd_path(char *cmd)
{
	char	*cwd;

	cwd = getcwd(0, 0);
	if (!cwd)
	{
		ft_putstr_fd(RED_COLOR, STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd("error retrieving current directory", STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd("getcwd: cannot access parent directories", STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		ft_putstr_fd(DEFAULT_COLOR, STDERR_FILENO);
	}
	return (cwd);
}

char	*get_new_pwd(char *path, bool flag, bool is_abs_path)
{
	char	*new_pwd;

	new_pwd = NULL;
	if (is_abs_path)
	{
		if (flag == false)
			new_pwd = get_cwd_path("cd");
		if (flag || new_pwd == NULL)
		{
			new_pwd = ft_strdup(path);
			if (!new_pwd)
				util_put_cmd_err_and_exit(NULL);
		}
	}
	else
	{
		new_pwd = get_cwd_path("cd");
		if (!new_pwd)
		{
			new_pwd = ft_strdup(path);
			if (!new_pwd)
				util_put_cmd_err_and_exit(NULL);
		}
	}
	return (new_pwd);
}
