/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect_util.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:47:37 by hommayunosu       #+#    #+#             */
/*   Updated: 2022/11/15 14:01:53 by nfukuma          ###   ########.fr       */
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

void	run_heredoc(char *limitter, t_redirect	*redirect)
{
	int		file;
	char	*buf;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		util_put_cmd_err_and_exit("in run_heredoc");
	while (1)
	{
		write(1, "> ", 2);
		buf = get_next_line(0);
		if (!buf)
			break ;
		if (!ft_strncmp(limitter, buf, ft_strlen(buf) - 1))
			break ;
		write(file, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	close(file);
	redirect->fd_file = open(".heredoc_tmp", O_RDONLY);
	if (redirect->fd_file < 0)
	{
		unlink(".heredoc_tmp");
		util_put_cmd_err_and_exit("in run_heredoc");
	}
}
