/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hommayunosuke <hommayunosuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:30:23 by hommayunosu       #+#    #+#             */
/*   Updated: 2022/11/16 17:30:24 by hommayunosu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	put_line_into_file(int file, char *buf, bool flag)
{
	if (flag == true)
	{
		write(file, "\n", 1);
	}
	write(file, buf, ft_strlen(buf));
	flag = true;
	return (flag);
}

void	heredoc_sigint_handler(int signal)
{
	extern t_shell	g_shell;

	g_shell.heredoc_interrupted = 1;
	g_shell.status = 128 + signal;
}

void	heredoc_signal_process(void)
{
	extern t_shell	g_shell;

	g_shell.heredoc_interrupted = 0;
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR || \
		signal(SIGINT, heredoc_sigint_handler) == SIG_ERR)
	{
		util_put_cmd_err_and_exit("in heredoc_signal_process()");
	}
}

int	heredoc_check_sigint(void)
{
	extern t_shell	g_shell;

	if (g_shell.heredoc_interrupted)
	{
		rl_done = 1;
	}
	return (0);
}

void	heredoc_readline_process(int file, char *limitter)
{
	char			*buf;
	bool			flag;
	extern t_shell	g_shell;

	flag = false;
	while (g_shell.heredoc_interrupted == 0)
	{
		buf = readline("> ");
		if (!buf || !ft_strcmp(limitter, buf))
			break ;
		buf = expand_env(buf);
		flag = put_line_into_file(file, buf, flag);
		free(buf);
		buf = NULL;
	}
	if (buf)
		free(buf);
}
