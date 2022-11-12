#include "../../includes/minishell.h"

t_redirect	*create_and_init_redirect(void)
{
	t_redirect	*ret;

	ret = (t_redirect *) malloc(sizeof(t_redirect));
	if (!ret)
		util_put_cmd_err_and_exit("malloc");
	ret->fd_io = NO_PID;
	ret->fd_file = NO_PID;
	ret->fd_backup = NO_PID;
	ret->filename = NULL;
	ret->next = NULL;
	ret->prev = NULL;
	return (ret);
}

void	delete_redirect_list(t_redirect **redirect)
{
	t_redirect	*tmp;
	t_redirect	*now;

	if (!redirect)
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
	if (token->type == CHAR_LESS)
		redirect->type = REDIR_INPUT;
	else if (token->type == CHAR_GREATER)
		redirect->type = REDIR_OUTPUT;
	else if (token->type == D_GREATER)
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
