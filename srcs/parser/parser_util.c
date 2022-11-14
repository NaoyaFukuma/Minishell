/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hommayunosuke <hommayunosuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:47:40 by hommayunosu       #+#    #+#             */
/*   Updated: 2022/11/14 22:47:41 by hommayunosu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_token_into_cmd_args(t_token_list **cmd_args, t_token_list **token)
{
	//cmd_argsにtokenの一つ目をまるまるコピーしたい
	//->するとtokenの一つ目のコピーを作ってあげて代入する必要がある
	t_token_list	*dup_token;
	//元のcmd_argsのアドレスを動かしたくないから別で最後尾のアドレスを持つ変数を宣言
	t_token_list	*cmd_args_tail;

	dup_token = duplicate_token(*token);
	if (!*cmd_args)
		*cmd_args = dup_token;
		//先頭じゃなかった場合は
	else
	{
		cmd_args_tail = *cmd_args;
		while (cmd_args_tail->next)
		{
			cmd_args_tail = cmd_args_tail->next;
		}
		cmd_args_tail->next = dup_token;
	}
}

void	input_cmd_args(t_command *command, t_token_list **token)
{
	while (*token && (*token)->type == TOKEN)
	{
		add_token_into_cmd_args(&command->args, token);
		*token = (*token)->next;
	}
}

//bool