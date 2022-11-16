/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:47:42 by hommayunosu       #+#    #+#             */
/*   Updated: 2022/11/15 14:02:21 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

bool	parse_redirect_process(t_node *node, t_token_list **token)
{
	t_redirect	*redirect;

	redirect = create_and_init_redirect();
	if ((*token)->type == IO_NUMBER)
	{
		if (ft_atoi_limit((*token)->comp, &redirect->fd_io) == false)
		{
			redirect->fd_io = REDIRECT_IO_NUM_ERROR;
			*token = (*token)->next;
		}
	}
	if (input_redirect_type_and_fd(*token, redirect) == false)
		return (false);
	*token = (*token)->next;
	if (!*token || (*token)->type != TOKEN)
	{
		delete_redirect_list(&redirect);
		return (false);
	}
	if ((*token)->prev->type == D_LESS)
		run_heredoc((*token)->comp, redirect, token);
	else
		add_token_into_original(&redirect->filename, *token);
	input_redirect(&node->command->redirects, redirect);
	return (true);
}

//cmdを入れてく関数
bool	parse_command(t_command **last_cmd, t_node **node, t_token_list **token)
{
	if (!*token)
		return (false);
	*node = create_and_init_node();
	if (*last_cmd)
		(*last_cmd)->next = (*node)->command;
	*last_cmd = (*node)->command;
	while (*token)
	{
		if ((*token)->type == TOKEN)
			input_cmd_args((*node)->command, token);
		else if ((*token)->type == CHAR_CLOSE_PARENTHESES)
			input_subshell_args((*node)->command, token);
		else if ((*token)->type == CHAR_LESS || (*token)->type == CHAR_GREATER \
				|| (*token)->type == D_GREATER || (*token)->type == D_LESS \
				|| (*token)->type == IO_NUMBER)
		{
			if (parse_redirect_process(*node, token) == false)
			{
				delete_node_list(node);
				return (false);
			}
		}
		else
			break ;
	}
	if (!(*node)->command->args && !(*node)->command->redirects)
	{
		delete_node_list(node);
		return (false);
	}
	return (true);
}

// print_parser((*node)->command);

bool	parse_logical_ope(t_command **last_cmd, t_node **node,
		t_token_list **token)
{
	t_node			*child;
	t_token_type	logi_type;

	if (*token && parse_command(last_cmd, node, token) == false)
		return (false);
	while (*token)
	{

		if ((*token)->type == AND_OPERATER || (*token)->type == OR_OPERATER)
		{
			logi_type = (*token)->type;
			(*token) = (*token)->next;
			if (!*token)
				return (false);
			if (parse_command(last_cmd, &child, token) == false)
				return (false);
			*node = add_parent_logi_node(*node, child, logi_type);
		}
		else
			break ;
	}
	return (true);
}

bool	parser(t_node **parent_node, t_token_list **token)
{
	t_node		*child;
	t_command	*last_cmd;

	*parent_node = NULL;
	last_cmd = NULL;
	if (*token && parse_logical_ope(&last_cmd, parent_node, token) == false)
		return (false);
	while (*token)
	{
		if ((*token)->type == CHAR_PIPE)
		{
			(*token) = (*token)->next;
			if (!*token)
				return (false);
			if (parse_logical_ope(&last_cmd, &child, token) == false)
				return (false);
			*parent_node = add_parent_node(*parent_node, child);
		}
		else
			break ;
	}
	return (true);
}
