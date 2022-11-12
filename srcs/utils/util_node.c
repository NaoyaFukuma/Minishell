#include "../../includes/minishell.h"

t_node	*create_and_init_node()
{
	t_node	*new_node;

	new_node = (t_node *) malloc(sizeof(t_node));
	if (!new_node)
		util_put_cmd_err_and_exit("malloc");
	new_node->command = (t_command *) malloc(sizeof(t_command));
	if (!new_node->command)
		util_put_cmd_err_and_exit("malloc");
	new_node->type = NODE_COMMAND;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->command->args = NULL;
	new_node->command->redirects = NULL;
	new_node->command->next = NULL;
	return (new_node);
}

t_node	*add_parent_node(t_node *left, t_node *right)
{
	t_node	*new_parent_node;

	new_parent_node = (t_node *) malloc(sizeof(t_node));
	if (!new_parent_node)
		util_put_cmd_err_and_exit("malloc");
	new_parent_node->type = NODE_PIPE;
	new_parent_node->command = NULL;
	new_parent_node->right = right;
	new_parent_node->left = left;
	return (new_parent_node);
}