/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hommayunosuke <hommayunosuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:47:42 by hommayunosu       #+#    #+#             */
/*   Updated: 2022/11/14 22:47:43 by hommayunosu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

bool	parse_redirect_process(t_node *node, t_token_list **token)
{
	t_redirect	*redirect;

	redirect = create_and_init_redirect();
	//数字指定ありリダイレクト
	if ((*token)->type == IO_NUMBER)
	{
		if (ft_atoi_limit((*token)->comp, &redirect->fd_io) == false) {
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
		{
			//nodeのargsにコマンドを入れてく処理
			input_cmd_args((*node)->command, token);
		}
		else if ((*token)->type == CHAR_LESS || (*token)->type == CHAR_GREATER \
				|| (*token)->type == D_GREATER || (*token)->type == IO_NUMBER)
		{
			//redirectの処理
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
	print_parser((*node)->command);
	return (true);
}

//前回のコマンドを保持する構造体に何をいれるのかわからない状況
bool	parser(t_node **parent_node, t_token_list **token)
{
	t_node		*child;
	t_command	*last_cmd;

	*parent_node = NULL;
	last_cmd = NULL;
	if (*token)
	{
		//親ノード(左側)に入れてく
		if (parse_command(&last_cmd, parent_node, token) == false)
			return (false);
	}
	while (*token)
	{
		if ((*token)->type == CHAR_PIPE)
		{
			(*token) = (*token)->next;
			if (!*token)
				return (false);
			//右側に入れてく
			if (parse_command(&last_cmd, &child, token) == false)
				return (false);
			//親ノードに移動する
			*parent_node = add_parent_node(*parent_node, child);
		}
		else
			break ;
	}
	return (true);
}
