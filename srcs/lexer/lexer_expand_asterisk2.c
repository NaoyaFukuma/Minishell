/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_asterisk2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 01:21:00 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/16 11:24:46 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_containing_asterisk(t_token_info *info)
{
	size_t	i;

	if (!info || !info->token || !info->token->comp ||
		info->each_i == 0)
		return (false);
	i = -1;
	while (++i <= info->each_i)
	{
		if (info->token->comp[i] == '*')
		{
			if (info->esc_flag && i > 0 && info->token->comp[i - 1] == '\\')
			{
				ft_memmove(&info->token->comp[i - 1], &info->token->comp[i],
						info->each_i - i);
				info->token->comp[info->each_i - 1] = '\0';
				return (false);
			}
			info->token->comp[info->each_i] = '\0';
			return (true);
		}
	}
	return (false);
}
