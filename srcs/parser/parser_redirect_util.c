/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect_util.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hommayunosuke <hommayunosuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:47:37 by hommayunosu       #+#    #+#             */
/*   Updated: 2022/11/16 00:16:34 by hommayunosu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redirect	*create_and_init_redirect(void)
{
	t_redirect	*ret;

	ret = (t_redirect *) malloc(sizeof(t_redirect));
	if (!ret)
		util_put_cmd_err_and_exit("malloc");
	ret->fd_io = REDIRECT_UNDEFINED;
	ret->fd_file = REDIRECT_UNDEFINED;
	ret->fd_backup = REDIRECT_UNDEFINED;
	ret->filename = NULL;
	ret->next = NULL;
	ret->prev = NULL;
	return (ret);
}

void	delete_redirect_list(t_redirect **redirect)
{
	t_redirect	*tmp;
	t_redirect	*now;

	if (!redirect || !*redirect)
		return ;
	now = *redirect;
	while (now)
	{
		tmp = now->next;
		del_token_list(&now->filename);
		now = tmp;
	}
	*redirect = NULL;
}

bool	input_redirect_type_and_fd(t_token_list *token, t_redirect *redirect)
{
	if (token->type == CHAR_LESS || token->type == D_LESS)
		redirect->type = REDIR_INPUT;
	else if (token->type == CHAR_GREATER)
		redirect->type = REDIR_OUTPUT;
	else if (token->type == D_GREATER)
		redirect->type = REDIR_APPEND_OUTPUT;
	else if (token->type == D_LESS)
		redirect->type = REDIR_APPEND_OUTPUT;
	else
	{
		delete_redirect_list(&redirect);
		return (false);
	}
	if (redirect->fd_io == REDIRECT_UNDEFINED)
	{
		if (redirect->type == REDIR_INPUT)
			redirect->fd_io = STDIN_FILENO;
		else
			redirect->fd_io = STDOUT_FILENO;
	}
	return (true);
}

void	input_redirect(t_redirect **dst, t_redirect *new)
{
	t_redirect	*now;

	if (!*dst)
		*dst = new;
	else
	{
		now = *dst;
		while (now->next)
			now = now->next;
		now->next = new;
		new->next = NULL;
		new->prev = now;
	}
}

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

/*
static void	heredoc_sigint_sighandler(int sig)
{
	g_shell.heredoc_interruption = 1;
	set_status(128 + sig);
}

void	cmd_set_heredoc_sighandlers(void)
{
	g_shell.heredoc_interruption = 0;
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR
		|| signal(SIGINT, heredoc_sigint_sighandler) == SIG_ERR)
	{
		printf("signal() failed\n");
		exit(1);
	}
}
*/

void	heredoc_sigint_handler(int signal)
{
	extern t_shell	g_shell;

	g_shell.heredoc_interrupted = 1;
	//signalをexit_statusにいれる処理したいけどふくまさん作ってたかも？
	g_shell.status = 128 + signal;
}

void	heredoc_signal_process()
{
	extern t_shell	g_shell;

	g_shell.heredoc_interrupted = 0;
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR || \
		signal(SIGINT, heredoc_sigint_handler) == SIG_ERR)
	{
		//signalのエラーの場合はどの関数使えばいいんだっけ
	}
}

void	run_heredoc(char *limitter, t_redirect	*redirect, t_token_list **token)
{
	int				file;
	char			*buf;
	bool			flag;
	extern t_shell	g_shell;

	flag = false;
	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		util_put_cmd_err_and_exit("in run_heredoc");
	heredoc_signal_process();
	while (!g_shell.heredoc_interrupted)
	{
//		printf("here: [%d]\n", g_shell.heredoc_interrupted);
		buf = readline("> ");
		if (!buf || !ft_strcmp(limitter, buf))
			break ;
		flag = put_line_into_file(file, buf, flag);
		free(buf);
	}
	free(buf);
	close(file);
	redirect->fd_file = open(".heredoc_tmp", O_RDONLY);
	unlink(".heredoc_tmp");
	if (redirect->fd_file < 0)
		util_put_cmd_err_and_exit("in run_heredoc");
	*token = (*token)->next;
}
