/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:11:05 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/17 00:11:21 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	util_put_syntax_error(void)
{
	extern t_shell	g_shell;

	if (g_shell.heredoc_interrupted)
	{
		g_shell.heredoc_interrupted = 0;
		return ;
	}
	ft_putstr_fd("\e[31mtsh: syntax error\n\e[m", STDERR_FILENO);
	g_shell.status = SYNTAX_ERROR;
}

void	util_put_cmd_err(char *command, char *message)
{
	ft_putstr_fd(RED_COLOR, STDERR_FILENO);
	ft_putstr_fd("tsh: ", STDERR_FILENO);
	if (command)
	{
		ft_putstr_fd(command, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(message, STDERR_FILENO);
	ft_putstr_fd(DEFAULT_COLOR, STDERR_FILENO);
}

void	util_put_cmd_err_and_exit(char *cmd)
{
	util_put_cmd_err(cmd, strerror(errno));
	exit(EXIT_FAILURE);
}

void	util_put_env_name_error(char *command, char *name)
{
	ft_putstr_fd("tsh: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

void	util_put_bad_fd_error(int fd)
{
	char	*fd_str;

	if (fd < 0)
		util_put_cmd_err("file descriptor out of range", strerror(errno));
	else
	{
		fd_str = ft_itoa(fd);
		if (!fd_str)
			util_put_cmd_err_and_exit("in util_put_bad_fd_error");
		util_put_cmd_err(fd_str, strerror(errno));
		free(fd_str);
	}
}
