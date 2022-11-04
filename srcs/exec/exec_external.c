/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:37:28 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/04 09:56:53 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_environ(t_env *envs)
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
			res_env = (char **)util_ptrarr_add_back((void **)res_env, (char *)env_str);
		}
		envs = envs->next;
	}
	return (res_env);
}

int	wait_cmd(pid_t pid)
{
	int	status;
	int	signal;

	if (waitpid(pid, &status, 0) == -1)
		util_put_cmd_err_and_exit("in wait_cmd");
	if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGINT)
			ft_putstr_fd("\n", STDERR_FILENO);
		if (signal == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		return (128 + signal);
	}
	return (WEXITSTATUS(status));
}

char	*get_binary_path(char *src_path)
{
	char	**split_paths;
	char	*res_path;
	size_t	i;

	if (!util_env_get("PATH") || !util_env_get("PATH")->value)
	{
		res_path = ft_strdup(src_path);
		if (!res_path)
			util_put_cmd_err_and_exit("in get_binary_path");
		return (res_path);
	}
	split_paths = util_colon_split(util_env_get("PATH")->value, ".");
	if (!split_paths)
		util_put_cmd_err_and_exit("in get_binary_path");
	i = - 1;
	while (split_paths[++i])
	{
		res_path = util_join_path(split_paths[i], src_path);
		if (access(res_path, X_OK) == 0)
			break ;
	}
	if (!split_paths[i])
		res_path = NULL;
	ft_safe_free_double_ptr((void ***)&split_paths);
	return (res_path);
}

char	*get_exe_path(char *src_path)
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

bool		is_executable(const char *path)
{
	t_stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (false);
	if ((path_stat.st_mode & S_IXUSR) != S_IXUSR)
		return (false);
	if ((path_stat.st_mode & S_IRUSR) != S_IRUSR)
		return (false);
	return (true);
}

void		execve_error_handle(char *path)
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

int	exec_external(char **args)
{
	pid_t	pid;
	char	*exe_path;
	char	**environ;
	extern t_shell	g_shell;

	pid = fork();
	if (pid == -1)
		util_put_cmd_err_and_exit("in exec_external");
	if (pid == 0)
	{
		set_sig_for_cmd_running();
		environ = create_environ(g_shell.envs);
		exe_path = get_exe_path(args[0]);
		printf("exepath %s\n", exe_path);
		execve(exe_path, args, environ);
		execve_error_handle(exe_path);
	}
	set_sig_for_wait_child();
	return (wait_cmd(pid));
}
