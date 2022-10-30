/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:46:26 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/30 21:52:50 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*set_dst_dir(char **args);
static bool	needs_cdpath(char **args, char *dst_dir);
static bool	try_cdpath(char *dst_dir);
static void	put_cd_err(char *dir, char *message);

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

static char	*set_dst_dir(char **args)
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

static bool	needs_cdpath(char **args, char *dst_dir)
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

static bool	try_cdpath(char *dst_dir)
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


static void	put_cd_err(char *dir, char *message)
{
	ft_putstr_fd(RED_COLOR, STDERR_FILENO);
	ft_putstr_fd("minishell: cd:", STDERR_FILENO);
	ft_putstr_fd(dir, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	ft_putstr_fd(DEFAULT_COLOR, STDERR_FILENO);
}
