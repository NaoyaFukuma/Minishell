/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect_util.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:47:37 by hommayunosu       #+#    #+#             */
/*   Updated: 2022/11/18 23:59:47 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

bool	run_heredoc(char *limitter, t_redirect	*redirect, t_token_list **token)
{
	int				file;
	extern t_shell	g_shell;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		util_put_cmd_err_and_exit("in run_heredoc");
	heredoc_signal_process();
	rl_event_hook = heredoc_check_sigint;
	heredoc_readline_process(file, limitter);
	close(file);
	redirect->fd_file = open(".heredoc_tmp", O_RDONLY);
	unlink(".heredoc_tmp");
	if (redirect->fd_file < 0)
		util_put_cmd_err_and_exit("in run_heredoc");
	rl_event_hook = NULL;
	*token = (*token)->next;
	set_sig_for_interactive_shell();
	if (g_shell.heredoc_interrupted == 1)
	{
		close(file);
		delete_redirect_list(&redirect);
		return (false);
	}
	return (true);
}
