/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:01:26 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/07 16:44:10 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define NOW_TOKEN 0
#define LAST_TOKEN 1
#define EXPANDED_TOKEN 2
#define FIRST_TOKEN 3

static void			token_join(t_token_list *prev_token,
						t_token_list *next_token);
static t_token_list	*find_last_token(t_token_list *tokens);

void	expander(t_token_list **tokens, bool ex_flag)
{
	t_token_list	*vars[4];
	char			*expanded_str;

	if (!tokens || !*tokens)
		return ;
	vars[LAST_TOKEN] = NULL;
	vars[FIRST_TOKEN] = NULL;
	vars[NOW_TOKEN] = *tokens;
	while (vars[NOW_TOKEN])
	{
		expanded_str = expand_env(vars[NOW_TOKEN]->comp, ex_flag);
		vars[EXPANDED_TOKEN] = lexer(expanded_str, true);
		free(expanded_str);
		if (vars[FIRST_TOKEN] == NULL)
			vars[FIRST_TOKEN] = vars[EXPANDED_TOKEN];
		token_join(vars[LAST_TOKEN], vars[EXPANDED_TOKEN]);
		vars[LAST_TOKEN] = find_last_token(vars[FIRST_TOKEN]);
		vars[NOW_TOKEN] = vars[NOW_TOKEN]->next;
	}
	del_token_list(tokens);
	*tokens = vars[FIRST_TOKEN];
}

static void	token_join(t_token_list *prev_token, t_token_list *next_token)
{
	if (!prev_token || !next_token || prev_token == next_token)
		return ;
	prev_token->next = next_token;
	next_token->prev = prev_token;
}

static t_token_list	*find_last_token(t_token_list *tokens)
{
	t_token_list	*now;

	if (!tokens)
		return (NULL);
	now = tokens;
	while (now->next != NULL)
		now = now->next;
	return (now);
}
