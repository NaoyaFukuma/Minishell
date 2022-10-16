NAME = minishell

SRCS_DIR = ./srcs

OBJS_DIR = ./objs

SRCS = $(wildcard $(SRCS_DIR)/*.c)

#INCLUDES = ../includes

OBJS = $(patsubst $(SRCS_DIR)/%, $(OBJS_DIR)/%, $(SRCS:.c=.o))

CFLAGS = -Wall -Werror -Wextra -I $(shell brew --prefix readline)/include

LIBS = -L $(shell brew --prefix readline)/lib -lreadline -lhistory

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
