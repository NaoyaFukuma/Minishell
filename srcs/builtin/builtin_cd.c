/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:46:26 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/26 14:37:11 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	put_cd_err(char *dir, char *message);

char	*set_dst_dir(char **args)
{
	t_env	*env;

	if (args[1])
		return (args[1]);
	env = util_env_get("HOME");
	if (!env)
	{
		util_put_cmd_err("cd", "HOME not set");
		return (NULL);
	}
	return (env->value ? env->value : "");
}

bool	needs_cdpath(char **args, char *dst_dir)
{
	if (args[1] == NULL || args[1][0] == '/')
		return (false);
	if (ft_strcmp(dst_dir, ".") == 0 ||
		ft_strcmp(dst_dir, "..") == 0 ||
		ft_strncmp(dst_dir, "./", 2) == 0 ||
		ft_strncmp(dst_dir, "../", 3) == 0)
		return (false);
	return (true);
}

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

bool	try_cdpath(char *dst_dir)
{
	char	**split_cdpath;
	bool	res;
	char	*try_chdir_res;
	extern t_shell	g_shell;

	res = false;
	split_cdpath = util_colon_split(util_env_get("CDPATH")->value, "");
	if (!split_cdpath)
		util_put_cmd_err_and_exit(NULL);
	try_chdir_res = try_splitted_cdpath(split_cdpath, dst_dir);
	if (try_chdir_res)
		res = true;
	if (res && ft_strlen(try_chdir_res) != 0)
		ft_putendl_fd(g_shell.pwd, STDOUT_FILENO);
	ft_safe_free_double_ptr((void ***)&split_cdpath);
	return (res);
}

int	builtin_cd(char **args)
{
	char	*dst_dir;
	extern t_shell	g_shell;

	dst_dir = set_dst_dir(args);
	if (!dst_dir)
		return (EXIT_FAILURE);
	if (needs_cdpath(args, dst_dir))
	{
		if (try_cdpath(dst_dir))
		{
			bind_pwd_value();
			return (EXIT_SUCCESS);
		}
	}
	else if (try_change_dir(dst_dir))
	{
		bind_pwd_value();
		return (EXIT_SUCCESS);
	}
	else
		put_cd_err(dst_dir, strerror(errno));
	return (EXIT_FAILURE);
}

static void	put_cd_err(char *dir, char *message)
{
	ft_putstr_fd(RED_COLOR, STDERR_FILENO);
	ft_putstr_fd("minishell: cd:", STDERR_FILENO);
	ft_putstr_fd(dir, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	ft_putstr_fd(WHITE_COLOR, STDERR_FILENO);
}
