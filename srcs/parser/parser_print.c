#include "../../includes/minishell.h"

static void	print_this(t_token_list *token)
{
	t_token_list	*tmp_token = token;

	while (tmp_token)
	{
		printf("comp: [%s]\n", tmp_token->comp);
		tmp_token = tmp_token->next;
	}
}

void	print_parser(t_command *cmd)
{
	t_command	*tmp_cmd;

	tmp_cmd = cmd;
	while (tmp_cmd)
	{
		print_this(tmp_cmd->args);
		tmp_cmd = tmp_cmd->next;
	}
}
