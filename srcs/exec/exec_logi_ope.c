/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logi_ope.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:41:59 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/13 11:37:38 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//
// void	exec_logi_ope(t_command *cmd)
// {
// 	extern t_shell	g_shell;
// 	t_pipe_state	pipe_state;
//
// 	pipe_state = NO_PIPE;
// 	g_shell.status = exec_cmd(cmd, &pipe_state, NULL);
// 	wait_external_cmds(cmd);
// 	if ((g_shell.status == 0 && cmd->logi_state == OR) || (g_shell.status != 0
// 			&& cmd->logi_state == AND))
// 		exit(g_shell.status);
// 	else
// 	{
// 		cmd = cmd->next;
// 		g_shell.status = exec_cmd(cmd, &pipe_state, NULL);
// 		wait_external_cmds(cmd);
// 		exit(g_shell.status);
// 	}
// }
