/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 09:28:27 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/30 21:22:24 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*set_cd_path(char *arg, bool *is_canon_path);
static int	cd_process(char *cd_path, char *arg, bool flag);

char	*try_splitted_cdpath(char **split_cd, char *dst_dir)
{
	size_t	i;
	char	*joined_dst_dir;

	i = -1;
	joined_dst_dir = NULL;
	while (split_cd[++i])
	{
		if (ft_strlen(split_cd[i]) == 0)
		{
			joined_dst_dir = ft_strdup(dst_dir);
			if (!joined_dst_dir)
				util_put_cmd_err_and_exit(NULL);
		}
		else
			joined_dst_dir = util_join_path(split_cd[i], dst_dir);
		if (try_change_dir(joined_dst_dir))
			break ;
	}
	ft_safe_free_single_ptr((void *)&joined_dst_dir);
	if (split_cd[i])
		return (split_cd[i]);
	return (NULL);
}

bool	try_change_dir(char *dst_path)
{
	char	*path;
	bool	is_canon_path_flag;
	int		res;

	path = set_cd_path(dst_path, &is_canon_path_flag);
	res = cd_process(path, dst_path, is_canon_path_flag);
	ft_safe_free_single_ptr((void **)&path);
	if (res == 0)
		return (true);
	return (false);
}

static char	*set_cd_path(char *arg, bool *is_canon_path)
{
	char			*canon_path;
	char			*physical_path;
	extern t_shell	g_shell;

	if (*arg == '/')
		physical_path = ft_strdup(arg);
	else
		physical_path = util_join_path(util_env_get("PWD")->value, arg);
	if (!physical_path)
		util_put_cmd_err_and_exit(NULL);
	canon_path = util_path_canonical(physical_path);
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

static int	cd_process(char *cd_path, char *arg, bool flag)
{
	int				res;
	int				err;
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
