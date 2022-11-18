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

# OBJS_DIR = ./objs

SRCS =	$(wildcard $(SRCS_DIR)/*.c) $(wildcard $(SRCS_DIR_BUILTIN)/*.c) \
		$(wildcard $(SRCS_DIR_EXEC)/*.c) $(wildcard $(SRCS_DIR_EXPANDER)/*.c) \
		$(wildcard $(SRCS_DIR_LEXER)/*.c) $(wildcard $(SRCS_DIR_PASER)/*.c) \
		$(wildcard $(SRCS_DIR_INIT)/*.c) $(wildcard $(SRCS_DIR_UTILS)/*.c) \
		$(wildcard $(SRCS_DIR_SIGNAL)/*.c)

INCLUDES = -I $(shell brew --prefix readline)/include -I ./libft -I ./includes -I ../includes

# OBJS = $(patsubst $(SRCS_DIR)/%, $(OBJS_DIR)/%, $(SRCS:.c=.o))
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address $(INCLUDES)

LIBS = -L $(shell brew --prefix readline)/lib -lreadline -lhistory -L ./libft -lft

all: $(NAME)

# User have to run brew install readline before run make to build minishell

$(NAME): $(OBJS)
	make -C ./libft
#	move ~/.inputrc ~/.inputrc_backup
	echo "set echo-control-characters off" >> ~/.inputrc
	$(CC) $(CFLAGS) $^ $(LIBS) -o $(NAME)

# $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@
#	mkdir -p $(OBJS_DIR)

clean:
	make clean -C ./libft
	$(RM) -r $(OBJS)
#	$(RM) -r $(OBJS_DIR)

fclean: clean
	make fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
