NAME = minishell
GCC = gcc

SRCS_DIR = ./srcs
SRCS_DIR_BUILTIN = ./srcs/builtin
SRCS_DIR_EXEC = ./srcs/exec
SRCS_DIR_EXPANDER = ./srcs/expander
SRCS_DIR_LEXER = ./srcs/lexer
SRCS_DIR_PASER = ./srcs/parser
SRCS_DIR_UTILS = ./srcs/utils
SRCS_DIR_INIT = ./srcs/init
SRCS_DIR_SIGNAL = ./srcs/signal

SRCS =	srcs/main.c srcs/builtin/builtin_cd1.c srcs/builtin/builtin_cd2.c srcs/builtin/builtin_cd3.c srcs/builtin/builtin_echo.c srcs/builtin/builtin_env.c srcs/builtin/builtin_exit.c srcs/builtin/builtin_export.c srcs/builtin/builtin_export_print.c srcs/builtin/builtin_export_sort.c srcs/builtin/builtin_pwd.c srcs/builtin/builtin_unset.c srcs/exec/args_util.c srcs/exec/exec.c srcs/exec/exec_cmd.c srcs/exec/exec_external.c srcs/exec/exec_external_util.c srcs/exec/pipe_util.c srcs/exec/redirect_util.c srcs/expander/expand_env.c srcs/expander/expand_env2.c srcs/expander/expander.c srcs/init/init_shell.c srcs/init/init_shell_util.c srcs/lexer/lexer.c srcs/lexer/lexer_expand_asterisk.c srcs/lexer/lexer_expand_asterisk2.c srcs/lexer/lexer_expand_asterisk3.c srcs/lexer/lexer_in_qoute.c srcs/lexer/lexer_not_in_qoute.c srcs/lexer/lexer_set_fin_nullchar_and_check_token_list.c srcs/parser/parser.c srcs/parser/parser_heredoc_util.c srcs/parser/parser_print.c srcs/parser/parser_redirect_util.c srcs/parser/parser_util.c srcs/signal/signal.c srcs/utils/util_create_prompt.c srcs/utils/util_env.c srcs/utils/util_env_list.c srcs/utils/util_error.c srcs/utils/util_node.c srcs/utils/util_path.c srcs/utils/util_path_canonical.c srcs/utils/util_token.c srcs/utils/utils.c

INCLUDES = -I $(shell brew --prefix readline)/include -I ./libft -I ./includes -I ../includes

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address $(INCLUDES)

LIBS = -L $(shell brew --prefix readline)/lib -lreadline -lhistory -L ./libft -lft

all: $(NAME)

# User have to run brew install readline before run make to build minishell

$(NAME): $(OBJS)
	make -C ./libft
	echo "set echo-control-characters off" >> ~/.inputrc
	$(CC) $(CFLAGS) $^ $(LIBS) -o $(NAME)

clean:
	make clean -C ./libft
	$(RM) -r $(OBJS)

fclean: clean
	make fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
