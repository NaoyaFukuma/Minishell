#include "../includes/minishell.h"
#include "../libft/libft.h"

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

void	add_token_into_cmd_args(t_token_list **cmd_args, t_token_list **token)
{
	//cmd_argsにtokenの一つ目をまるまるコピーしたい
	//->するとtokenの一つ目のコピーを作ってあげて代入する必要がある
	t_token_list	*dup_token;
	//元のcmd_argsのアドレスを動かしたくないから別で最後尾のアドレスを持つ変数を宣言
	t_token_list	*cmd_args_tail;

	dup_token = duplicate_token(*token);
	if (!*cmd_args)
		*cmd_args = dup_token;
	//先頭じゃなかった場合は
	else
	{
		cmd_args_tail = *cmd_args;
		while (cmd_args_tail->next)
		{
			cmd_args_tail = cmd_args_tail->next;
		}
		cmd_args_tail->next = dup_token;
		/* ここがわからない
		dup_token->prev = cmd_args_tail->next;
		*/
	}
}

void	input_cmd_args(t_command *command, t_token_list **token)
{
	while (*token && (*token)->type == TOKEN)
	{
		add_token_into_cmd_args(&command->args, token);
		*token = (*token)->next;
	}
}

//cmdを入れてく関数
void	parse_command(t_node **node, t_token_list **token)
{
	if (!*node)
		return ;
	*node = create_and_init_node();
	//前回のコマンドを記録
	while (*token)
	{
		if ((*token)->type == TOKEN)
		{
			//nodeのargsにコマンドを入れてく処理
			input_cmd_args((*node)->command, token);
		}
		else if ((*token)->type == CHAR_LESS || (*token)->type == CHAR_GREATER \
					(*token)->type == D_GREATER || (*token)->type == IO_NUMBER)
		{
			//redirectの処理
		}
		else
			break ;
	}
}

t_node	*add_parent_node(t_node *left, t_node *right)
{
	t_node	*new_parent_node;

	new_parent_node = (t_node *) malloc(sizeof(t_node));
	if (!new_parent_node)
		util_put_cmd_err_and_exit("malloc");
	new_parent_node->type = NODE_PIPE;
	new_parent_node->command = NULL;
	new_parent_node->right = *right;
	new_parent_node->left = *left;
	return (new_parent_node);
}

//前回のコマンドを保持する構造体に何をいれるのかわからない状況
void	parser(t_node **parent_node, t_token_list **token)
{
	t_node	*child;

	if (*token)
	{
		//親ノード(左側)に入れてく
		parse_command(parent_node, token);
	}
	while (*token)
	{
		if ((*token)->type == CHAR_PIPE)
		{
			(*token) = (*token)->next;
			if (!*token)
				return ;
			//右側に入れてく
			parse_command(&child, token);
			//親ノードに移動する
			*parent_node = add_parent_node(*parent_node, child);
		}
		else
			break ;
	}
}
