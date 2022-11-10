/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_in_qoute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:13:00 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/10 00:46:11 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_quote_lexer(t_token_info *info, t_token_type type, char *str)
{
	(void)type;
	info->token->comp[info->each_i++] = str[info->str_i];
	if (str[info->str_i] == CHAR_QUOTE)
	{
		info->status = NOT_QUOTED;
		if (info->esc_flag == true)
			info->each_i -= 1;
	}
}

void	in_parentheses_lexer(t_token_info *info, t_token_type type, char *str)
{
	info->token->comp[info->each_i++] = str[info->str_i];
	if (str[info->str_i] == CHAR_CLOSE_PARENTHESES)
	{
		info->token->type = type;
		info->status = NOT_QUOTED;
		if (info->esc_flag == true)
			info->each_i -= 1;
	}
}

void	in_d_quote_lexer(t_token_info *info, t_token_type type, char *str)
{
	if (type == CHAR_BACKSLASH && str[info->str_i + 1] != '\0' &&
		ft_strchr("\"\\$", str[info->str_i + 1]) != NULL)
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
	{
		info->token->comp[info->each_i++] = str[info->str_i];
		if (str[info->str_i] == CHAR_D_QUOTE)
		{
			info->status = NOT_QUOTED;
			if (info->esc_flag == true)
				info->each_i -= 1;
		}
	}
}
