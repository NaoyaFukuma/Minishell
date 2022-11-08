/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:17:50 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/08 16:51:24 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_list(t_node *nodes);
static void	exec_pipeline(t_node *nodes);
static int	exec_cmd(t_command *cmd, t_pipe_state *pipe_state, int *old_pipe);
static void		update_pipe_state(t_command *cmd, t_pipe_state *pipe_state);

void	exec_nodes(t_node *nodes)
{
	extern t_shell	g_shell;

	if (!nodes || g_shell.exited == true)
		return ;
	if (nodes->type == NODE_SEMICOLON)
	{
		exec_nodes(nodes->left);
		exec_nodes(nodes->right);
	}
	else
		exec_list(nodes);
}

static void	exec_list(t_node *nodes)
{
	extern t_shell	g_shell;
	t_pipe_state	pipe_state;

	pipe_state = NO_PIPE;
	if (!nodes)
		return ;
	if (nodes->type == NODE_PIPE)
		exec_pipeline(nodes);
	else
	{
		g_shell.status = exec_cmd(nodes->command, &pipe_state, NULL);
		wait_external_cmds(nodes->command);
	}
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
	cmd = nodes->command;
	while (cmd)
	{
		g_shell.status = exec_cmd(cmd, &pipe_state, pipe);
		cmd = cmd->next;
	}
	wait_external_cmds(nodes->command);
}

static void		update_pipe_state(t_command *cmd, t_pipe_state *pipe_state)
{
	if (*pipe_state == NO_PIPE)
		return ;
	if (cmd->next && cmd->next->next)
		*pipe_state = PIPE_READ_WRITE;
	else
		*pipe_state = PIPE_READ_ONLY;
}

static int	exec_cmd(t_command *cmd, t_pipe_state *pipe_state, int *old_pipe)
{
	char	**args;
	int		status;

	status = EXIT_SUCCESS;
	token_to_args(cmd, &args);

	if (*pipe_state == NO_PIPE && util_is_builtin(args[0]))
		status = exec_builtin_parent(cmd, args);
	else
		exec_cmd_child(cmd, args, *pipe_state, old_pipe);
	redirects_util_cleanup(cmd);
	update_pipe_state(cmd, pipe_state);
	ft_safe_free_double_ptr((void ***)&args);
	return (status);
}
