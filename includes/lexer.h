/*#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum	e_token_type
{
	CHAR_BACKSLASH = '\\',
	CHAR_SEMICOLON = ';',
	CHAR_QUOTE = '\'',
	CHAR_D_QUOTE = '\"',
	CHAR_PIPE = '|',
	CHAR_LESS = '<',
	CHAR_GREATER = '>',
	CHAR_SPACE = ' ',
	CHAR_TAB = '\t',
	CHAR_OTHER,
}				t_token_type;

typedef enum	e_token_status
{
	QUOTED,
	D_QUOTED,
	NOT_QUOTED,
}				t_token_status;

typedef struct	s_token_list	t_token_list;

struct	s_token_list
{
	t_token_list	*prev;
	t_token_list	*next;
	t_token_type	type;
	char 			*comp; //component
};

typedef struct	s_token_info
{
	size_t			str_i;
	//それぞれのトークンのindex
	size_t			each_i;
	size_t			len;
	t_token_list	*first_token;
	t_token_list	*token;
	bool			quote_flag;
	t_token_status	status;
}				t_token_info;

t_token_list	*lexer(char *str);

#endif
*/