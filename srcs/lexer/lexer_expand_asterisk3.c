/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_asterisk3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 23:16:50 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/26 15:00:40 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_backslash(char *str)
{
	size_t	i;

	i = -1;
	while (str[++i])
	{
		if(str[i] == '\\')
			ft_memmove(&str[i], &str[i + 1], ft_strlen(&str[i + 1]) + 1);
	}
}

bool	is_match(t_each_str *each_str, char **target)
{
	remove_backslash(each_str->str);
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
			if (info->esc_flag && i > 0 && info->token->comp[i - 1] != '\\')
				return (true);
			if (i == 0)
				return (true);
		}
	}
	remove_backslash(info->token->comp);
	return (false);
}

void	aster_escape(t_expander *exper)
{
	char	*tmp;
	char	*result;

	result = ft_substr(exper->str, 0, exper->str_i);
	tmp = result;
	result = ft_strjoin(result, "\\");
	free(tmp);
	tmp = result;
	result = ft_strjoin(result, &exper->str[exper->str_i]);
	free(tmp);
	free(exper->str);
	exper->str = result;
	exper->str_i++;
}
