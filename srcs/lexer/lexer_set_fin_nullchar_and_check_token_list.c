/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_set_fin_nullchar_and_check_token_list        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:51:03 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/07 12:55:21 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_token_error(t_token_status state);
static void	del_token_list(t_token_list **token_p);
static void	del_token(t_token_list **token_p);

void	set_fin_nullchar_and_check_token_list(t_token_info *info)
{
	if (info->status != NOT_QUOTED)
	{
		print_token_error(info->status);
		del_token_list(&(info->first_token));
		return ;
	}
	if (info->each_i == 0 && info->quote_flag == false)
	{
		if (info->first_token == info->token)
			del_token_list(&info->first_token);
		else
			del_token(&info->token);
	}
	else
		info->token->comp[info->each_i] = '\0';
}

static void	print_token_error(t_token_status state)
{
	extern t_shell	g_shell;

	if (state == D_QUOTED)
		util_put_cmd_err(NULL,
				"unexpected EOF while looking for matching `\"'");
	if (state == QUOTED)
		util_put_cmd_err(NULL, "unexpected EOF while looking for matching `''");
	g_shell.status = TOKEN_ERROR;
}

static void	del_token_list(t_token_list **token_p)
{
	t_token_list	*now;
	t_token_list	*tmp;

	if (!token_p || !*token_p)
		return ;
	now = *token_p;
	while (now)
	{
		tmp = now->next;
		del_token(&now);
		now = tmp;
	}
	*token_p = NULL;
}

static void	del_token(t_token_list **token_p)
{
	t_token_list	*token;

	if (!token_p || !*token_p)
		return ;
	token = *token_p;
	if (token->comp)
		free(token->comp);
	if (token->next)
		token->next->prev = token->prev;
	if (token->prev)
		token->prev->next = token->next;
	free(token);
	*token_p = NULL;
}
