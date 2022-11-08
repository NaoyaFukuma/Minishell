#include "minishell.h"

t_shell	g_shell;

static void	run_cmdline(char *line);
static void	ctrl_d_exit_put_msg(void);

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

static void	run_cmdline(char *line)
{
	extern t_shell	g_shell;
	// t_node 			*nodes;
	t_token_list	*tokens;
	// t_token_list	*start_token_for_free;

	tokens = lexer(line, false);
	// start_token_for_free = tokens;
	// nodes = perser(tokens);
	// if (!nodes)
		// put_syntax_error(tokens);

	// 疑似パーサー
	t_command cmds = {tokens, NULL, NO_PID, NULL};
	t_node nodes = {NODE_COMMAND, &cmds, NULL, NULL};
	//
	exec_nodes(&nodes);
	// del_token_list(&start_token_for_free);
	// del_node_list(&nodes);
	return ;
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
