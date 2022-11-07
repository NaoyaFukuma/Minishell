/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_not_in_qoute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 00:04:02 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/07 13:01:44 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	char_set_token(t_token_info *info, t_token_type type, char *str);
static void	token_separate(t_token_info *info, t_token_type type, char *str);
static bool	is_io_number_token(t_token_info *info, t_token_type type);
static void	tokeniser_add_new_token(t_token_info *info);

void	not_in_quote_lexer(t_token_info *info, t_token_type type, char *str)
{
	if (type == CHAR_OTHER || type == CHAR_QUOTE || type == CHAR_D_QUOTE
		|| type == CHAR_BACKSLASH)
	{
		char_set_token(info, type, str);
		if (type == CHAR_QUOTE)
		{
			info->status = QUOTED;
			info->quote_flag = true;
			if (info->esc_flag)
				info->each_i -= 1;
		}
		else if (type == CHAR_D_QUOTE)
		{
			info->status = D_QUOTED;
			info->quote_flag = true;
			if (info->esc_flag)
				info->each_i -= 1;
		}
		else
			info->status = NOT_QUOTED;
		info->token->type = TOKEN;
	}
	else
		token_separate(info, type, str);
}

static void	char_set_token(t_token_info *info, t_token_type type, char *str)
{
	if (type == CHAR_BACKSLASH && str[info->str_i + 1] != '\0')
	{
		if (info->esc_flag)
			info->token->comp[info->each_i++] = str[++info->str_i];
		else
		{
			info->token->comp[info->each_i++] = str[info->str_i++];
			info->token->comp[info->each_i++] = str[info->str_i];
		}
	}
	else
		info->token->comp[info->each_i++] = str[info->str_i];
}

static void	token_separate(t_token_info *info, t_token_type type, char *str)
{
	if (is_io_number_token(info, type))
		info->token->type = IO_NUMBER;
	tokeniser_add_new_token(info);
	if (type != CHAR_SPACE && type != CHAR_TAB)
	{
		info->token->comp[info->each_i++] = str[info->str_i];
		if (str[info->str_i + 1] == str[info->str_i])
		{
			if (type == CHAR_GREATER)
			{
				info->token->comp[info->each_i++] = str[++info->str_i];
				type = D_GREATER;
			}
			else if (type == CHAR_SEMICOLON)
			{
				info->token->comp[info->each_i++] = str[++info->str_i];
				type = D_SEMICOLON;
			}
		}
		info->token->type = type;
		tokeniser_add_new_token(info);
	}
}

static bool	is_io_number_token(t_token_info *info, t_token_type type)
{
	size_t	i;

	if (!info || !info->token || !info->token->comp ||
		info->each_i == 0 ||
		(type != CHAR_GREATER && type != CHAR_LESS))
		return (false);
	i = info->each_i;
	while (i != 0 && ft_isdigit(info->token->comp[i - 1]))
		i--;
	if (i == 0)
		return (true);
	return (false);
}

static void	tokeniser_add_new_token(t_token_info *info)
{
	t_token_list	*tmp_token;

	if (info->each_i > 0 || (info->quote_flag))
	{
		info->token->comp[info->each_i] = '\0';
		tmp_token =
			init_token(info->token, info->len - info->str_i);
		info->token->next = tmp_token;
		info->token = tmp_token;
		info->each_i = 0;
		info->quote_flag = false;
	}
}
