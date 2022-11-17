/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 00:11:52 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/17 15:45:24 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define FILE_MODE 0644

static bool	check_filename(t_redirect *redirect, char *org_filename);
static int	open_file(t_redirect *redirect);

bool	redirect_util_setup(t_command *cmd)
{
	t_redirect	*redirect;
	char		*origin_file;

	redirect = cmd->redirects;
	while (redirect)
	{
		origin_file = ft_strdup(redirect->filename->comp);
		if (!origin_file)
			util_put_cmd_err_and_exit("in redirects");
		expander(&redirect->filename);
		if (!check_filename(redirect, origin_file))
		{
			free(origin_file);
			return (false);
		}
		free(origin_file);
		redirect = redirect->next;
	}
	return (true);
}

static bool	check_filename(t_redirect *redirect, char *org_filename)
{
	if (redirect->filename == NULL || redirect->filename->next)
	{
		util_put_cmd_err(org_filename, "ambiguous redirect");
		return (false);
	}
	redirect->fd_file = open_file(redirect);
	if (redirect->fd_file < 0)
	{
		util_put_cmd_err(strerror(errno), redirect->filename->comp);
		return (false);
	}
	return (true);
}

static int	open_file(t_redirect *redirect)
{
	char	*filename;

	filename = redirect->filename->comp;
	if (redirect->type == REDIR_INPUT)
		return (open(filename, O_RDONLY));
	if (redirect->type == REDIR_OUTPUT)
		return (open(filename, O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE));
	return (open(filename, O_WRONLY | O_CREAT | O_APPEND, FILE_MODE));
}

void	redirects_util_cleanup(t_command *command)
{
	t_redirect	*redirect;

	redirect = command->redirects;
	while (redirect && redirect->next)
		redirect = redirect->next;
	while (redirect)
	{
		if (redirect->fd_file >= 0 && close(redirect->fd_file) < 0)
			util_put_cmd_err_and_exit("in redirects_util_cleanup");
		if (redirect->fd_backup >= 0 && (dup2(redirect->fd_backup,
					redirect->fd_io) < 0 || close(redirect->fd_backup) < 0))
			util_put_cmd_err_and_exit("in redirects_util_cleanup");
		redirect = redirect->prev;
	}
}

bool	redirect_util_dupfd(t_command *command, bool is_parent)
{
	t_redirect	*redirect;

	redirect = command->redirects;
	while (redirect)
	{
		if (is_parent)
		{
			redirect->fd_backup = dup(redirect->fd_io);
			if (redirect->fd_backup < 0)
			{
				util_put_bad_fd_error(redirect->fd_io);
				return (false);
			}
		}
		if (dup2(redirect->fd_file, redirect->fd_io) < 0)
		{
			util_put_bad_fd_error(redirect->fd_io);
			return (false);
		}
		redirect = redirect->next;
	}
	return (true);
}
