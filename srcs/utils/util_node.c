/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:47:50 by hommayunosu       #+#    #+#             */
/*   Updated: 2022/11/15 00:53:50 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	new_node->command->pid = NO_PID;
	new_node->command->next = NULL;
	new_node->command->logi_state = NO_OPE;
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
	new_parent_node->left->command->logi_state = NO_OPE;
	return (new_parent_node);
}

t_node	*add_parent_logi_node(t_node *left, t_node *right ,t_token_type	logi_type)
{
	t_node	*new_parent_node;

	new_parent_node = (t_node *) malloc(sizeof(t_node));
	if (!new_parent_node)
		util_put_cmd_err_and_exit("malloc");
	new_parent_node->type = NODE_OPERATER;
	new_parent_node->command = NULL;
	new_parent_node->right = right;
	new_parent_node->left = left;
	if (logi_type == AND_OPERATER)
		new_parent_node->left->command->logi_state = AND;
	if (logi_type == OR_OPERATER)
		new_parent_node->left->command->logi_state = OR;
	return (new_parent_node);
}

void	delete_node_list(t_node **node)
{
	if (!node || !*node)
		return ;
	if ((*node)->type == NODE_COMMAND && (*node)->command)
	{
		delete_token_list(&(*node)->command->args);

	}
}
