/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 09:28:27 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/26 16:30:00 by nfukuma          ###   ########.fr       */
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
	char *cwd;

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
		ft_putstr_fd(WHITE_COLOR, STDERR_FILENO);
	}
	return (cwd);
}

char	*get_new_pwd(char *path, bool flag, bool is_abs_path)
{
	char *new_pwd;

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

int		cd_process(char *cd_path, char *arg, bool flag)
{
	int			res;
	int			err;
	extern t_shell	g_shell;

	res = chdir(cd_path);
	if (res == 0)
	{
		ft_safe_free_single_ptr((void **)&g_shell.pwd);
		g_shell.pwd = get_new_pwd(cd_path, flag, true);
		return (res);
	}
	err = errno;
	res = chdir(arg);
	if (res == 0)
	{
		ft_safe_free_single_ptr((void **)&g_shell.pwd);
		g_shell.pwd = get_new_pwd(cd_path, flag, false);
		return (res);
	}
	errno = err;
	res = EXIT_FAILURE;
	return (res);
}

char	*set_cd_path(char *arg, bool *is_canon_path)
{
	char			*canon_path;
	char			*physical_path;
	extern t_shell	g_shell;

	if (*arg == '/')
		physical_path = ft_strdup(arg);
	else
		physical_path = util_join_path(g_shell.pwd, arg);
	if (!physical_path)
		util_put_cmd_err_and_exit(NULL);
	canon_path = path_canonical(physical_path);
	if (canon_path)
	{
		ft_safe_free_single_ptr((void **)&physical_path);
		*is_canon_path = true;
		return (canon_path);
	}
	else
	{
		ft_safe_free_single_ptr((void **)&canon_path);
		*is_canon_path = false;
		return (physical_path);
	}
}

bool	try_change_dir(char *dst_path)
{
	char	*path;
	bool	is_canon_path_flag;
	int		res;

	path = set_cd_path(dst_path, &is_canon_path_flag);
	res = cd_process(path, dst_path, is_canon_path_flag);
	ft_safe_free_single_ptr((void **)&path);
	return (res);
}
