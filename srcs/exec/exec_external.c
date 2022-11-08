/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:37:28 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/08 14:41:38 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_environ(t_env *envs);
static char	*get_exe_path(char *src_path);
static void	execve_error_handle(char *path);

void	exec_external(char **args)
{
	char			*exe_path;
	char			**environ;
	extern t_shell	g_shell;

	environ = create_environ(g_shell.envs);
	exe_path = get_exe_path(args[0]);
	execve(exe_path, args, environ);
	execve_error_handle(exe_path);
}

static char	**create_environ(t_env *envs)
{
	char	**res_env;
	char	*env_str;
	char	*tmp_for_free;

	res_env = NULL;
	while (envs)
	{
		if (envs->is_env && envs->value)
		{
			env_str = ft_strjoin(envs->name, "=");
			if (!env_str)
				util_put_cmd_err_and_exit("in create_environ");
			tmp_for_free = env_str;
			env_str = ft_strjoin(env_str, envs->value);
			if (!env_str)
				util_put_cmd_err_and_exit("in create_environ");
			free(tmp_for_free);
			res_env = (char **)util_ptrarr_add_back((void **)res_env,
					(char *)env_str);
		}
		envs = envs->next;
	}
	return (res_env);
}

static char	*get_exe_path(char *src_path)
{
	char	*res_path;

	if (!src_path)
		return (NULL);
	if (!ft_strchr(src_path, '/'))
	{
		res_path = get_binary_path(src_path);
		if (!res_path)
		{
			util_put_cmd_err(src_path, "command not found");
			exit(CMD_NOT_FOUND);
		}
	}
	else
	{
		res_path = ft_strdup(src_path);
		if (!res_path)
			util_put_cmd_err_and_exit("in get_exe_path");
	}
	return (res_path);
}

static void	execve_error_handle(char *path)
{
	int	status;

	if (errno == ENOENT)
		status = CMD_NOT_FOUND;
	else
		status = CMD_NOT_EXECUTABLE;
	if (util_is_directory(path))
	{
		util_put_cmd_err(path, "is a directory");
		exit(status);
	}
	if (errno == ENOEXEC && !is_executable(path))
		errno = EACCES;
	if (errno == ENOEXEC)
		exit(EXIT_SUCCESS);
	util_put_cmd_err(path, strerror(errno));
	exit(status);
}


