/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 23:42:47 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/31 10:38:34 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_int_handle(int sig);

void	set_sig_for_interactive_shell(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR || signal(SIGINT, sig_int_handle) == SIG_ERR)
		util_put_cmd_err_and_exit("set signal");
}

static void	sig_int_handle(int sig)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	util_set_status(128 + sig);
}
