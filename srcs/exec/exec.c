// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   exec.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/11/04 15:17:50 by nfukuma           #+#    #+#             */
// /*   Updated: 2022/11/07 10:20:21 by nfukuma          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */
//
// #include "minishell.h"
//
// static void		exec_list(t_node_list *nodes);
// static void		exec_pipeline(t_node_list *nodes);
//
// void			exec_nodes(t_node_list *nodes)
// {
// 	extern t_shell g_shell;
//
// 	if (!nodes || g_shell.exited == true)
// 		return ;
// 	if (nodes->type == NODE_SEMICOLON)
// 	{
// 		exec_nodes(nodes->left);
// 		exec_nodes(nodes->right);
// 	}
// 	else
// 		exec_list(nodes);
// }
//
// static void		exec_list(t_node_list *nodes)
// {
// 	extern t_shell	g_shell;
// 	t_pipe_state	pipe_state;
//
// 	pipe_state = NO_PIPE;
// 	if (!nodes)
// 		return ;
// 	if (nodes->type == NODE_PIPE)
// 		exec_pipeline(nodes);
// 	else
// 	{
// 		g_shell.status = exec_cmd(nodes->cmd, &pipe_state, NULL);
// 		(nodes->cmd);
// 		wait_commands(nodes->cmd);
// 	}
// }
//
// static void		exec_pipeline(t_node_list *nodes)
// {
// 	extern t_shell	g_shell;
// 	t_cmd			*cmd;
// 	int				pipe[2];
// 	t_pipe_state	pipe_state;
//
// 	pipe_state = PIPE_WRITE_ONLY;
// 	while (nodes->type == NODE_PIPE)
// 		nodes = nodes->left;
// 	cmd = nodes->cmd;
// 	while (cmd)
// 	{
// 		g_shell.status = exec_cmd(cmd, &pipe_state, pipe);
// 		cmd = cmd->next;
// 	}
// 	wait_commands(nodes->cmd);
// }
//
// int	exec_cmd(t_cmd *cmd, t_pipe_state *state, int *old_pipe)
// {
// 	char	**args;
// 	int		status;
//
// 	status = EXIT_SUCCESS;
// 	convert_tokens(cmd, &args);
// 	if (*state == NO_PIPE && util_is_builtin(args))
// 		status = exec_builtin_parent(cmd, args);
//
// }
