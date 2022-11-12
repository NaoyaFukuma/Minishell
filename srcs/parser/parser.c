#include "../../includes/minishell.h"
#include "../../libft/libft.h"

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

t_redirect	*create_and_init_redirect(void)
{
	t_redirect	*ret;

	ret = (t_redirect *) malloc(sizeof(t_redirect));
	if (!ret)
		util_put_cmd_err_and_exit("malloc");
	ret->fd_io = NO_PID;
	ret->fd_file = NO_PID;
	ret->fd_backup = NO_PID;
	ret->filename = NULL;
	ret->next = NULL;
	ret->prev = NULL;
	return (ret);
}

void	delete_redirect_list(t_redirect **redirect)
{
	t_redirect	*tmp;
	t_redirect	*now;

	if (!redirect)
		return ;
	now = *redirect;
	while (now)
	{
		tmp = now->next;
		del_token_list(&now->filename);
		now = tmp;
	}
	*redirect = NULL;
}

bool	input_redirect_type_and_fd(t_token_list *token, t_redirect *redirect)
{
	if (token->type == CHAR_LESS)
		redirect->type = REDIR_INPUT;
	else if (token->type == CHAR_GREATER)
		redirect->type = REDIR_OUTPUT;
	else if (token->type == D_GREATER)
		redirect->type = REDIR_APPEND_OUTPUT;
	else
	{
		delete_redirect_list(&redirect);
		return (false);
	}
	if (redirect->fd_io == REDIRECT_UNDEFINED)
	{
		if (redirect->type == REDIR_INPUT)
			redirect->fd_io = STDIN_FILENO;
		else
			redirect->fd_io = STDOUT_FILENO;
	}
	return (true);
}

void	input_redirect(t_redirect **dst, t_redirect *new)
{
	t_redirect	*now;

	if (!*dst)
		*dst = new;
	else
	{
		now = *dst;
		while (now->next)
			now = now->next;
		now->next = new;
		new->next = NULL;
		new->prev = now;
	}
}

bool	parse_redirect_process(t_node *node, t_token_list **token)
{
	t_redirect	*redirect;

	redirect = create_and_init_redirect();
	//数字指定ありリダイレクト
	if ((*token)->type == IO_NUMBER)
	{
		if (ft_atoi_limit((*token)->comp, &redirect->fd_io) == false) {
			redirect->fd_io = REDIRECT_IO_NUM_ERROR;
			*token = (*token)->next;
		}
	}
	if (input_redirect_type_and_fd(*token, redirect) == false)
		return (false);
	*token = (*token)->next;
	if (!*token || (*token)->type != TOKEN)
	{
		delete_redirect_list(&redirect);
		return (false);
	}
	add_token_into_original(&redirect->filename, *token);
	input_redirect(&node->command->redirects, redirect);
	return (true);
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

void	print_this(t_token_list *token)
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

//cmdを入れてく関数
bool	parse_command(t_command *last_cmd, t_node **node, t_token_list **token)
{
	if (!*node)
		return (false);
	*node = create_and_init_node();
	if (last_cmd)
		last_cmd->next = (*node)->command;
	else // last_cmd == NULL
		last_cmd = (*node)->command;
	//前回のコマンドを記録
	while (*token)
	{
		if ((*token)->type == TOKEN)
		{
			//nodeのargsにコマンドを入れてく処理
			input_cmd_args((*node)->command, token);
		}
		else if ((*token)->type == CHAR_LESS || (*token)->type == CHAR_GREATER \
				|| (*token)->type == D_GREATER || (*token)->type == IO_NUMBER)
		{
			//redirectの処理
			parse_redirect_process(*node, token);
		}
		else
			break ;
	}
	/*この処理の起こるときがあまり理解できてない
	if (!(*node)->command->args && !(*node)->command->redirects)
	{
		del_node_list(node);
		return (FALSE);
	}
	*/
	print_parser((*node)->command);
	return (true);
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

//前回のコマンドを保持する構造体に何をいれるのかわからない状況
bool	parser(t_node **parent_node, t_token_list **token)
{
	t_node		*child;
	t_command	last_cmd;

	if (*token)
	{
		//親ノード(左側)に入れてく
		if (parse_command(&last_cmd, parent_node, token) == false)
			return (false);
	}
	while (*token)
	{
		if ((*token)->type == CHAR_PIPE)
		{
			(*token) = (*token)->next;
			if (!*token)
				return (false);
			//右側に入れてく
			if (parse_command(&last_cmd, &child, token) == false)
				return (false);
			//親ノードに移動する
			*parent_node = add_parent_node(*parent_node, child);
		}
		else
			break ;
	}
	return (true);
}
