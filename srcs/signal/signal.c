/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 23:42:47 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/15 11:12:11 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_int_handle(int sig);

void	set_sig_for_interactive_shell(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR || signal(SIGINT, sig_int_handle) == SIG_ERR)
		util_put_cmd_err_and_exit("in set_sig_for_interactive_shell()");
}

void	set_sig_for_wait_child(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR || signal(SIGINT, SIG_IGN) == SIG_ERR)
		util_put_cmd_err_and_exit("in set_sig_for_interactive_shell()");
}

void	set_sig_for_cmd_running(void)
{
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR || signal(SIGINT, SIG_DFL) == SIG_ERR)
		util_put_cmd_err_and_exit("in set_sig_for_cmd_running()");
}

static void	sig_int_handle(int sig)
{
	extern t_shell	g_shell;
	int	i;

	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
	ft_putstr_fd("\e[1G", 1);
	ft_putstr_fd("\e[31m[1]\e[m", 1);
	ft_putstr_fd("\e[1G", 1);
	i = -1;
	while (++i < g_shell.prompt_len)
		ft_putstr_fd("\e[1C", 1);
	g_shell.status = 1;
	g_shell.interrupted = true;
}
