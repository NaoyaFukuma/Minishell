#include "../../includes/lexer.h"
#include "../../includes/minishell.h"

//#include "../../libft/libft.h"

#include "lexer.h"

t_token_list	*init_token(t_token_list *prev)
{
	t_token_list	*ret_token;

	ret_token = malloc(sizeof(t_token_list));
	if (!ret_token)
	{
		//未処理
		printf("malloc error\n");
	}
	//未処理　確保する領域の範囲を修正
	ret_token->comp = malloc(sizeof(char) * 100);
	if (!ret_token->comp)
	{
		//未処理
		printf("malloc error\n");
	}
	ret_token->next = NULL;
	ret_token->prev = prev;
	//ret_token->type = ;
	ret_token->comp[0] = '\0';
	return (ret_token);
}

void	init_token_info(t_token_info *token_info, char *av)
{
	token_info->str_i = 0;
	token_info->each_i = 0;
	token_info->len = ft_strlen(av);
	token_info->token = init_token(NULL);
	token_info->first_token = token_info->token;
	token_info->quote_flag = false;
}

t_token_type	get_token_type(char c)
{
	if (c == '\\')
		return (CHAR_BACKSLASH);
	else if (c == ';')
		return (CHAR_SEMICOLON);
	else if (c == '\'')
		return (CHAR_QUOTE);
	else if (c == '\"')
		return (CHAR_D_QUOTE);
	else if (c == '|')
		return (CHAR_PIPE);
	else if (c == '<')
		return (CHAR_LESS);
	else if (c == '>')
		return (CHAR_GREATER);
	else if (c == ' ')
		return (CHAR_SPACE);
	else if (c == '\t')
		return (CHAR_TAB);
	else
		return (CHAR_OTHER);
}

void	add_new_token_list(t_token_info *token_info, t_token_type type)
{
	t_token_list	*new_token;

	token_info->token->comp[token_info->each_i] = '\0';
//	printf("check : %s\n", token_info->token->comp);
	new_token = init_token(token_info->token);
	token_info->token->next = new_token;
	//トークンのアドレスを変更することで現在のトークンは実質空みたいに
	token_info->token = new_token;
	token_info->each_i = 0;
	token_info->quote_flag = false;
	token_info->status = NOT_QUOTED;
}

void	other_type_process(t_token_info *token_info, t_token_type type, char *str)
{
	//quotedの処理書く？
	if (token_info->each_i != 0 && (type == CHAR_SPACE || type == CHAR_TAB))
	{
		add_new_token_list(token_info, type);
	}
	if (type == CHAR_QUOTE || type == CHAR_D_QUOTE)
	{
		if (type == CHAR_QUOTE)
			token_info->status = QUOTED;
		else
			token_info->status = D_QUOTED;
		token_info->quote_flag = true;
		token_info->token->comp[token_info->each_i++] = str[token_info->str_i];
	}
	else if (type == CHAR_PIPE){

	}
//	add_new_token_list(token_info, type);
}

t_token_list	*split_token(char *av)
{
	t_token_info	token_info;
	t_token_type	type;

	init_token_info(&token_info, av);
	//全ての文字は一つずつこのwhile文でみていくのがいいかも
	while (av[token_info.str_i] != '\0')
	{
		type = get_token_type(av[token_info.str_i]);
		if (token_info.quote_flag == false)
		{
			//特殊な文字じゃないときの普通の処理
			if (type == CHAR_OTHER)
			{
				token_info.token->comp[token_info.each_i++] = av[token_info.str_i];
			}
			//新しいトークンが必要な処理->CHAR_OTHERじゃない処理
			else
			{
				other_type_process(&token_info, type, av);
			}
		}
		else
		{
			if (token_info.status == QUOTED && type == CHAR_QUOTE)
			{
				token_info.token->comp[token_info.each_i++] = av[token_info.str_i];
				token_info.quote_flag = false;
			}
			else if (token_info.status == D_QUOTED && type == CHAR_D_QUOTE)
			{
				token_info.token->comp[token_info.each_i++] = av[token_info.str_i];
				token_info.quote_flag = false;
			}
			//quote内の文字をどんどんいれる
			else
			{
				token_info.token->comp[token_info.each_i++] = av[token_info.str_i];
			}
		}
		token_info.str_i++;
	}
	token_info.token->comp[token_info.each_i] = '\0';
	return (token_info.first_token);
}

int main(int ac, char **av)
{
	t_token_list	*token;
	if (ac != 2)
		return (1);
	printf("av : %s\n", av[1]);
	token = split_token(av[1]);
	int i = 0;
	while (token)
	{
		printf("%d [%s]\ttype->[%d]\n", i, token->comp, token->type);
		token = token->next;
		i++;
	}
	return (0);
}
