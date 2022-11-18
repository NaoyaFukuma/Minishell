/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_asterisk3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 23:16:50 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/18 23:54:07 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_match(t_each_str *each_str, char **target)
{
	if (!each_str->prev_as)
	{
		if (ft_strncmp(*target, each_str->str, ft_strlen(each_str->str)))
			return (false);
		else
			*target += ft_strlen(each_str->str);
	}
	else if (!each_str->next_as)
	{
		if (ft_strncmp(&(*target)[ft_strlen(*target)
				- ft_strlen(each_str->str)], each_str->str,
			ft_strlen(each_str->str)))
			return (false);
	}
	else
	{
		*target = ft_strnstr(*target, each_str->str, ft_strlen(*target));
		if (!*target)
			return (false);
		else
			*target += ft_strlen(each_str->str);
	}
	return (true);
}

bool	is_containing_asterisk(t_token_info *info)
{
	size_t	i;

	if (!info || !info->token || !info->token->comp || info->each_i == 0)
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
