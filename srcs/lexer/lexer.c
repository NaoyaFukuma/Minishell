/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 01:34:33 by hommayunosu       #+#    #+#             */
/*   Updated: 2022/11/10 00:46:52 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			init_token_info(t_token_info *token_info, char *str,
						bool esc_flag);

// debug
void	print_type(t_token_type type)
{
	char	*str;

	str = NULL;
	if (type == CHAR_BACKSLASH)
		str = "\\";
	else if (type == CHAR_SEMICOLON)
		str = ";";
	else if (type == CHAR_QUOTE)
		str = "\'";
	else if (type == CHAR_D_QUOTE)
		str = "\"";
	else if (type == CHAR_PIPE)
		str = "|";
	else if (type == CHAR_LESS)
		str = "<";
	else if (type == CHAR_GREATER)
		str = ">";
	else if (type == CHAR_SPACE)
		str = "SPACE";
	else if (type == CHAR_TAB)
		str = "TAB";
	else if (type == CHAR_OTHER)
		str = "OTHER";
	else if (type == TOKEN)
		str = "TOKEN";
	else if (type == CHAR_OPEN_PARENTHESES)
		str = "(";
	else if (type == CHAR_CLOSE_PARENTHESES)
		str = ")";
	else if (type == CHAR_NIL)
		str = "(NULL)";
	printf("type->[%s]\n", str);
}
//
// void	print_status(t_token_status status)
// {
// 	char	*str;
//
// 	str = NULL;
// 	if (status == QUOTED)
// 		str = "QUOTED";
// 	else if (status == D_QUOTED)
// 		str = "QUOTED";
// 	else if (status == PARENTHESESED)
// 		str = "PARENTHESESED";
// 	else if (status == NOT_QUOTED)
// 		str = "NOT_QUOTED";
// 	printf("status->[%s]\n", str);
// }


t_token_list	*lexer(char *str, bool esc_flag)
{
	t_token_info	token_info;
	t_token_type	type;

	init_token_info(&token_info, str, esc_flag);
	while (str[token_info.str_i] != '\0')
	{
		type = get_token_type(str[token_info.str_i]);
		if (token_info.status == NOT_QUOTED)
			not_in_quote_lexer(&token_info, type, str);
		else if (token_info.status == QUOTED)
			in_quote_lexer(&token_info, type, str);
		else if (token_info.status == D_QUOTED)
			in_d_quote_lexer(&token_info, type, str);
		else if (token_info.status == PARENTHESESED)
			in_parentheses_lexer(&token_info, type, str);
		token_info.str_i++;
	}
	set_fin_nullchar_and_check_token_list(&token_info);

	// debug
	t_token_list	*tmp_for_print;
	size_t			i;

	printf("original: [%s]\n", str);
	tmp_for_print = token_info.first_token;
	i = 0;
	while (tmp_for_print)
	{
		printf("%zu [%s]\t", i, tmp_for_print->comp);
		print_type(tmp_for_print->type);
		tmp_for_print = tmp_for_print->next;
		i++;
	}
	// debug end

	return (token_info.first_token);
}

t_token_list	*init_token(t_token_list *prev, size_t len)
{
	t_token_list	*ret_token;

	ret_token = malloc(sizeof(t_token_list));
	if (!ret_token)
		util_put_cmd_err_and_exit("in init_token");
	ret_token->comp = malloc(len + 1);
	if (!ret_token->comp)
		util_put_cmd_err_and_exit("in init_token");
	ret_token->comp[0] = '\0';
	ret_token->next = NULL;
	ret_token->prev = prev;
	ret_token->type = TOKEN;
	return (ret_token);
}

static void	init_token_info(t_token_info *token_info, char *str, bool esc_flag)
{
	token_info->len = ft_strlen(str);
	token_info->token = init_token(NULL, token_info->len);
	token_info->first_token = token_info->token;
	token_info->str_i = 0;
	token_info->each_i = 0;
	token_info->status = NOT_QUOTED;
	token_info->quote_start = NULL;
	token_info->esc_flag = esc_flag;
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
	else if (c == '\0')
		return (CHAR_NIL);
	else if (c == '&')
		return (CHAR_AMPERSAND);
	else if (c == '(')
		return (CHAR_OPEN_PARENTHESES);
	else if (c == ')')
		return (CHAR_CLOSE_PARENTHESES);
	else
		return (CHAR_OTHER);
}
