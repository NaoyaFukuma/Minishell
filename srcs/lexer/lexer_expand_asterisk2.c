/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_asterisk2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 01:21:00 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/26 14:57:20 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_info(t_as_info *info, char *src_str)
{
	info->src_str = src_str;
	info->str_i = 0;
	info->start_i = 0;
	info->prev_as = false;
	info->next_as = false;
	info->res = NULL;
}

t_each_str	*create_new_node(t_as_info *info)
{
	t_each_str	*new;

	new = malloc(sizeof(t_each_str));
	if (!new)
		util_put_cmd_err_and_exit("in new_node");
	new->prev_as = info->prev_as;
	new->next_as = info->next_as;
	if (info->next_as)
		info->prev_as = true;
	else
		info->prev_as = false;
	info->next_as = false;
	return (new);
}

void	create_each_str_add_back(t_as_info *info)
{
	t_each_str	*tmp;
	t_each_str	*new;

	new = create_new_node(info);
	new->str = ft_substr(info->src_str, info->start_i, info->str_i
			- info->start_i);
	if (!new->str)
		util_put_cmd_err_and_exit("in new_node");
	new->next = NULL;
	if (!info->res)
		info->res = new;
	else
	{
		tmp = info->res;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

bool	is_wildcard_expandble(char *target, t_each_str *each_str)
{
	bool	res;

	if (!each_str)
		return (true);
	while (each_str)
	{
		res = is_match(each_str, &target);
		if (!res)
			return (false);
		each_str = each_str->next;
	}
	return (true);
}

void	del_each_str_list(t_each_str *each_str)
{
	t_each_str	*tmp;

	if (!each_str)
		return ;
	while (each_str)
	{
		tmp = each_str->next;
		free(each_str->str);
		free(each_str);
		each_str = tmp;
	}
}
