/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_sort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:08:01 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/07 22:14:29 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*merge_step(t_env *left, t_env *right, int (*cmp)());
static t_env	*sep_step(t_env *lst, int (*cmp)());
static int		comp_func(t_env *left, t_env *right);

void	env_sort_for_export(t_env **lst)
{
	*lst = sep_step(*lst, comp_func);
}

static t_env	*sep_step(t_env *lst, int (*cmp)())
{
	t_env	*left;
	t_env	*right;
	t_env	*right_head;

	if (lst == NULL || lst->next == NULL)
		return (lst);
	left = lst;
	right = lst->next;
	if (right != NULL)
		right = right->next;
	while (right != NULL)
	{
		left = left->next;
		right = right->next;
		if (right != NULL)
			right = right->next;
	}
	right_head = left->next;
	left->next = NULL;
	return (merge_step(sep_step(lst, cmp), sep_step(right_head, cmp), cmp));
}

static int	comp_func(t_env *left, t_env *right)
{
	return (ft_strcmp(left->name, right->name));
}

static t_env	*merge_step(t_env *left, t_env *right, int (*cmp)())
{
	t_env	elem;
	t_env	*next;

	next = &elem;
	while (left != NULL && right != NULL)
	{
		if (cmp(left, right) < 0)
		{
			next->next = left;
			next = next->next;
			left = left->next;
		}
		else
		{
			next->next = right;
			next = next->next;
			right = right->next;
		}
	}
	if (left == NULL)
		next->next = right;
	else
		next->next = left;
	return (elem.next);
}
