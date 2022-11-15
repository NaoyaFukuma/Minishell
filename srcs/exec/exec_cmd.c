/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:28:38 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/15 00:10:14 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd_child(t_command *cmd, char **args, t_pipe_state pipe_state,
		int old_pipe[])
{
	int	new_pipe[2];

	pipe_util_create_new_pipe(pipe_state, new_pipe);
	cmd->pid = fork();
	if (cmd->pid < 0)
		util_put_cmd_err_and_exit("in exec_cmd_child");
	if (cmd->pid == 0)
	{
		set_sig_for_cmd_running();
		if (redirect_util_setup(cmd) == false)
			exit(EXIT_FAILURE);
		if (args[0] == NULL)
			exit(EXIT_SUCCESS);
		pipe_util_setup(pipe_state, old_pipe, new_pipe);
		if (redirect_util_dupfd(cmd, false) == false)
			exit(EXIT_FAILURE);
		if (util_is_builtin(args[0]))
			exit(exec_builtin(args));
		else
			exec_external(args);
	}
	set_sig_for_wait_child();
	pipe_util_cleanup(pipe_state, old_pipe, new_pipe);
}

int	exec_cmd_parent(t_command *command, char **args)
{
	if (!redirect_util_setup(command))
		return (EXIT_FAILURE);
	if (!redirect_util_dupfd(command, true))
		return (EXIT_FAILURE);
	return (exec_builtin(args));
}

int	exec_builtin(char **args)
{
	if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args));
	if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args));
	if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env());
	if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args));
	if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args));
	return (EXIT_FAILURE);
}
