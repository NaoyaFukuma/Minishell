/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:46:26 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/24 01:52:52 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	put_cd_err(char *dir, char *message);

int	builtin_cd(char **args)
{
	char	*dst_dir;
	extern t_shell	g_shell;

	// cd only
	if (!args[1])
	{
		if (chdir(util_env_get("HOME")->value) == -1)
		{
			util_put_cmd_err("cd", strerror(errno));
			return (EXIT_FAILURE);
		}
		else
		{
			util_set_env("OLDPWD", util_env_get("PWD") ? util_env_get("PWD")->value : NULL, ENV_TRUNC);
			util_env_set("PWD", util_env_get("HOME")->value, ENV_TRUNC);
			return (EXIT_SUCCESS);
		}
	}

	// cd -
	if (!ft_strcmp(args[1], "-"))
	{
		if (!util_env_get("OLDPWD"))
		{
			util_put_cmd_err("cd", "OLDPWD not set");
			return (EXIT_FAILURE);
		}
		if (chdir(util_env_get("OLDPWD")->value) == -1)
		{
			util_put_cmd_err("cd", strerror(errno));
			return (EXIT_FAILURE);
		}
		else
		{
			util_env_set("PWD", util_env_get("OLDPWD")->value, ENV_TRUNC);
			return (EXIT_SUCCESS);
		}
	}

	dst_dir = args[1];
	if (util_env_get("CDPATH"))
	{
		char	**cd_paths;
		char	*joined_path;
		char	*tmp_path;
		cd_paths = ft_split(util_env_get("CDPATH")->value, ':');
		if (!cd_paths)
			util_perror_and_exit("malloc");
		while (*cd_paths)
		{
			tmp_path = ft_strjoin(*cd_paths, "/");
			joined_path = ft_strjoin(tmp_path, dst_dir);
			free(tmp_path);
			if (chdir(joined_path) == -1)
			{
				util_put_cmd_err("cd", strerror(errno));
				return (EXIT_FAILURE);
			}
			else
			{
				util_set_env("OLDPWD", util_env_get("PWD") ? util_env_get("PWD")->value : NULL, ENV_TRUNC);
				util_env_set("PWD", joined_path, ENV_TRUNC);
				free(joined_path);
				return (EXIT_SUCCESS);
			}
			cd_paths++;
		}
		free(cd_paths);
	}



	if (ft_strcmp(dst_dir, ".") == 0 ||
		ft_strcmp(dst_dir, "..") == 0 ||
		ft_strncmp(dst_dir, "./", 2) == 0 ||
		ft_strncmp(dst_dir, "../", 3) == 0)
	{
		if (chdir(dst_dir) == -1)
		{
			util_put_cmd_err("cd", strerror(errno));
			return (EXIT_FAILURE);
		}
		else
		{
			util_set_env("OLDPWD", util_env_get("PWD") ? util_env_get("PWD")->value : NULL, ENV_TRUNC);
			util_env_set("PWD", dst_dir, ENV_TRUNC);
			return (EXIT_SUCCESS);
		}
	}
	else
	{
		dst_dir = malloc(ft_strlen(util_env_get("PWD")->value) + ft_strlen(args[1]))
	}



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
