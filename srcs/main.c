#include "minishell.h"

t_shell	g_shell;

static void	ctrl_d_exit_put_msg(void);

char	**tokens_convert_args(t_token_list *tokens)
{
	char	**res_args;
	char	**tmp_for_free;

	res_args = NULL;
	while (tokens)
	{
		tmp_for_free = res_args;
		res_args = (char **)util_ptrarr_add_back((void *)res_args, (void *)ft_strdup(tokens->comp));
		if (!res_args)
			util_put_cmd_err_and_exit("in tokens_conbert_args");
		free(tmp_for_free);
		tokens = tokens->next;
	}
	return (res_args);
}

static void	run_cmdline(char *line)
{
	extern t_shell	g_shell;
	t_token_list	*tokens;
	char			**cmd_args;
	// t_token_list	*start_token_for_free;
	// t_node			*nodes;

	tokens = lexer(line, false);
	cmd_args = tokens_convert_args(tokens);
	if (util_is_builtin(cmd_args[0]))
		g_shell.status = exec_builtin(cmd_args);
	else
		g_shell.status = exec_external(cmd_args);
	ft_safe_free_double_ptr((void ***)&cmd_args);
	// tokens = lexer(line);
	// start_token_for_free = tokens;
	// if (parser(&nodes, &tokens) == false) // 未着手
		// put_parse_syntax_error(tokens); // 未着手
	// del_token_list(&start_token_for_free);
	// del_node_list(&nodes);
	return ;
}

int	main(int argc, char **argv)
{
	extern t_shell	g_shell;
	char	*line;
	char	*prompt;

	init_minishell();
	if (argc > 2 && !ft_strcmp(argv[1], "-c"))
	{
		g_shell.interactive = false;
		run_cmdline(argv[2]);
	}
	else
	{
		g_shell.interactive = true;
		while (1)
		{
			g_shell.interrupted = false;
			g_shell.exited = false;
			set_sig_for_interactive_shell();
			prompt = util_create_prompt_str();
			line = readline(prompt);
			free(prompt);
			if (line == NULL)
				break ;
			if (*line)
			{
				add_history(line);
				run_cmdline(line);
			}
			free(line);
		}
		ctrl_d_exit_put_msg();
	}
	exit(EXIT_SUCCESS);
}

static void	ctrl_d_exit_put_msg(void)
{
	char	*prompt_len_str;
	char	*screen_ctrl_str;

	ft_putstr_fd(UP_LINE_CURSOR, STDERR_FILENO);
	prompt_len_str = ft_itoa((int)g_shell.prompt_len);
	if (!prompt_len_str)
		util_put_cmd_err_and_exit("malloc");
	screen_ctrl_str = util_join_and_free_err_exit("\e[", false, prompt_len_str, true);
	screen_ctrl_str = util_join_and_free_err_exit(screen_ctrl_str, true, "C", false);
	ft_putstr_fd(screen_ctrl_str, STDERR_FILENO);
	free(screen_ctrl_str);
	ft_putstr_fd("exit\n", STDERR_FILENO);
}
