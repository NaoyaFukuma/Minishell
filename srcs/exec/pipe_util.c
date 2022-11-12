/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:18:02 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/13 00:20:00 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	can_write(t_pipe_state state)
{
	if (state == PIPE_WRITE_ONLY || state == PIPE_READ_WRITE)
		return (true);
	return (false);
}

static bool	can_read(t_pipe_state pipe_state)
{
	if (pipe_state == PIPE_READ_ONLY || pipe_state == PIPE_READ_WRITE)
		return (true);
	return (false);
}

void	pipe_util_create_new_pipe(t_pipe_state pipe_state, int new_pipe[])
{
	if (can_write(pipe_state) == true && pipe(new_pipe) < 0)
		util_put_cmd_err_and_exit("in create_pipe");
}

void	pipe_util_setup(t_pipe_state state, int old_pipe[], int new_pipe[])
{
	if (can_read(state) == true)
		if (close(old_pipe[PIPE_WRITE]) < 0 ||
			dup2(old_pipe[PIPE_READ], STDIN_FILENO) < 0 ||
			close(old_pipe[PIPE_READ]) < 0)
			util_put_cmd_err_and_exit("in dup_pipe");
	if (can_write(state) == true)
		if (close(new_pipe[PIPE_READ]) < 0 ||
			dup2(new_pipe[PIPE_WRITE], STDOUT_FILENO) < 0 ||
			close(new_pipe[PIPE_WRITE]) < 0)
			util_put_cmd_err_and_exit("in dup_pipe");
}

void			pipe_util_cleanup(t_pipe_state state, int old_pipe[], int new_pipe[])
{
	if (can_read(state) == true)
		if (close(old_pipe[PIPE_READ]) < 0 || close(old_pipe[PIPE_WRITE]) < 0)
			util_put_cmd_err_and_exit("pipe_util_cleanup");
	if (can_write(state) == true)
	{
		old_pipe[PIPE_READ] = new_pipe[PIPE_READ];
		old_pipe[PIPE_WRITE] = new_pipe[PIPE_WRITE];
	}
}
