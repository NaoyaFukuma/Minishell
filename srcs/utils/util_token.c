#include "../../includes/minishell.h"

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