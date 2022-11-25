/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:36:08 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/26 00:54:10 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	i = -1;
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

bool	is_executable(const char *path)
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

static void	cmd_status_handler(int status, bool catch_sigint)
{
	extern t_shell	g_shell;
	int				signal;

	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 200)
			g_shell.status = SYNTAX_ERROR;
		else
			g_shell.status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		g_shell.status = 128 + signal;
	}
	if (catch_sigint)
		ft_putstr_fd("\n", STDERR_FILENO);
}

void	wait_external_cmds(t_command *cmd)
{
	extern t_shell	g_shell;
	int				status;
	bool			has_child;
	bool			catch_sigint;

	has_child = false;
	catch_sigint = false;
	while (cmd)
	{
		if (cmd->pid != NO_PID)
		{
			if (waitpid(cmd->pid, (int *)&status, 0) == -1)
				util_put_cmd_err_and_exit("in wait_cmd");
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				catch_sigint = true;
			has_child = true;
		}
		cmd = cmd->next;
	}
	if (has_child == false)
		return ;
	cmd_status_handler(status, catch_sigint);
}

void	wait_external_cmd(t_command *cmd)
{
	extern t_shell	g_shell;
	int				status;
	bool			has_child;
	bool			catch_sigint;

	has_child = false;
	catch_sigint = false;
	if (cmd->pid != NO_PID)
	{
		if (waitpid(cmd->pid, &status, 0) == -1)
			util_put_cmd_err_and_exit("in wait_cmd");
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			catch_sigint = true;
		has_child = true;
		cmd->pid = NO_PID;
	}
	if (has_child == false)
		return ;
	cmd_status_handler(status, catch_sigint);
}
