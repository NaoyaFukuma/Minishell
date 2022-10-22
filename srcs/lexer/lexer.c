//#include "../../includes/lexer.h"
//#include "../../includes/minishell.h"

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
	token_info->first_token = token_info->token;
	token_info->token = init_token(NULL);
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

void	add_new_token_list(t_token_info *token_info)
{
	t_token_list	*new_token;

	new_token = init_token(token_info->token);
	token_info->token->next = new_token;
	//トークンのアドレスを変更することで現在のトークンは実質空みたいに
	token_info->token = new_token;
	token_info->each_i = 0;
	token_info->quote_flag = false;
}

void	go_next_token(t_token_info *token_info, t_token_type type)
{
	add_new_token_list(token_info);
}

//abc | def

void	split_token(char *av)
{
	t_token_info	token_info;
	t_token_type	type;

	init_token_info(&token_info, av);
	while (av[token_info.str_i] != '\0')
	{
//		while (i < 1)
//		{
			type = get_token_type(av[token_info.str_i]);
			if (token_info.quote_flag == false)
			{
				//特殊な文字じゃないときの普通の処理
				if (type == CHAR_OTHER)
				{
					printf("hoge\n");
					token_info.token->comp[token_info.each_i] = av[token_info.str_i];
					token_info.str_i++;
				}
				//'\'の次の文字をリストに
				else if (type == CHAR_BACKSLASH)
				{
					token_info.token->comp[token_info.each_i] = av[++token_info.str_i];
					token_info.str_i++;
				}
				//新しいトークンが必要な処理
				else
				{
					go_next_token(&token_info, type);
					token_info.str_i++;
				}
			}
			token_info.each_i++;
//		}
	}
//	for (size_t i = 0; )
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	split_token(av[1]);
}