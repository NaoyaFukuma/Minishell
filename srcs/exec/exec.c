/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:17:50 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/26 00:54:46 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_list(t_node *nodes);
static void	exec_pipeline(t_node *nodes);
static void	update_pipe_state(t_command *cmd, t_pipe_state *pipe_state);

void	exec_nodes(t_node *nodes)
{
	extern t_shell	g_shell;

	if (!nodes || g_shell.exited == true)
		return ;
	exec_list(nodes);
}

static void	exec_list(t_node *nodes)
{
	extern t_shell	g_shell;
	t_command		*cmd;
	t_pipe_state	pipe_state;

	pipe_state = NO_PIPE;
	if (nodes->type == NODE_PIPE)
		exec_pipeline(nodes);
	while (nodes->type == NODE_OPERATER)
		nodes = nodes->left;
	cmd = nodes->command;
	while (cmd)
	{
		g_shell.status = exec_cmd(cmd, &pipe_state, NULL);
		if (cmd->logi_state == OR || cmd->logi_state == AND)
		{
			wait_external_cmd(cmd);
			if ((cmd->logi_state == OR && (g_shell.status == EXIT_SUCCESS))
				|| (cmd->logi_state == AND && g_shell.status != EXIT_SUCCESS))
				cmd = cmd->next;
		}
		cmd = cmd->next;
	}
	wait_external_cmds(nodes->command);
}

static void	exec_pipeline(t_node *nodes)
{
	extern t_shell	g_shell;
	t_command		*cmd;
	int				pipe[2];
	t_pipe_state	pipe_state;

	pipe_state = PIPE_WRITE_ONLY;
	while (nodes->type == NODE_PIPE)
		nodes = nodes->left;
	while (nodes->type == NODE_OPERATER)
		nodes = nodes->left;
	cmd = nodes->command;
	while (cmd)
	{
		g_shell.status = exec_cmd(cmd, &pipe_state, pipe);
		if (cmd->logi_state == OR || cmd->logi_state == AND)
		{
			wait_external_cmd(cmd);
			if ((cmd->logi_state == OR && (g_shell.status == EXIT_SUCCESS))
				|| (cmd->logi_state == AND && g_shell.status != EXIT_SUCCESS))
				cmd = cmd->next;
		}
		cmd = cmd->next;
	}
	wait_external_cmds(nodes->command);
}

static void	update_pipe_state(t_command *cmd, t_pipe_state *pipe_state)
{
	if (*pipe_state == NO_PIPE)
		return ;
	if (cmd->next && cmd->next->next)
		*pipe_state = PIPE_READ_WRITE;
	else
		*pipe_state = PIPE_READ_ONLY;
}

int	exec_cmd(t_command *cmd, t_pipe_state *pipe_state, int *old_pipe)
{
	char	**args;
	int		status;

	status = EXIT_SUCCESS;
	token_to_args(cmd, &args);
	if (*pipe_state == NO_PIPE && util_is_builtin(args[0]))
		status = exec_cmd_parent(cmd, args);
	else
		exec_cmd_child(cmd, args, *pipe_state, old_pipe);
	redirects_util_cleanup(cmd);
	update_pipe_state(cmd, pipe_state);
	ft_safe_free_double_ptr((void ***)&args);
	return (status);
}
