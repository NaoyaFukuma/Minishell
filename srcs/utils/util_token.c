/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:47:47 by hommayunosu       #+#    #+#             */
/*   Updated: 2022/11/17 15:06:42 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_token(t_token_list **token_list)
{
	t_token_list	*token;

	if (!token_list || !*token_list)
		return ;
	token = *token_list;
	if (token->comp)
		free(token->comp);
	if (token->next)
		token->next->prev = token->prev;
	if (token->prev)
		token->prev->next = token->next;
	free(token);
	*token_list = NULL;
}

void	delete_token_list(t_token_list **token_list)
{
	t_token_list	*tmp;
	t_token_list	*now;

	if (!token_list || !*token_list)
		return ;
	now = *token_list;
	while (now)
	{
		tmp = now->next;
		delete_token(&now);
		now = tmp;
	}
	*token_list = NULL;
}

t_token_list	*duplicate_token(t_token_list *token)
{
	t_token_list	*dup_token;
	size_t			comp_len;

	comp_len = ft_strlen(token->comp);
	dup_token = init_token(NULL, comp_len);
	ft_strlcpy(dup_token->comp, token->comp, comp_len + 1);
	dup_token->type = token->type;
	return (dup_token);
}

void	add_token_into_original(t_token_list **token, t_token_list *original)
{
	t_token_list	*now;
	t_token_list	*dup_token;

	original->comp = expand_env(original->comp);
	dup_token = duplicate_token(original);
	if (!*token)
		*token = dup_token;
	else
	{
		now = *token;
		while (now->next)
			now = now->next;
		now->next = dup_token;
		dup_token->prev = now->next;
	}
}
