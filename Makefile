NAME = minishell

SRCS_DIR = ./srcs

OBJS_DIR = ./objs

SRCS = $(wildcard $(SRCS_DIR)/*.c)

#INCLUDES = ../includes

OBJS = $(patsubst $(SRCS_DIR)/%, $(OBJS_DIR)/%, $(SRCS:.c=.o))

CFLAGS = -Wall -Werror -Wextra -I $(shell brew --prefix readline)/include -I ./libft -I ./includes

LIBS = -L $(shell brew --prefix readline)/lib -lreadline -lhistory -L ./libft -lft

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) $^ $(LIBS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C ./libft
	$(RM) -r $(OBJS_DIR)

fclean: clean
	make fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
