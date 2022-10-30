#include "minishell.h"

t_shell	g_shell;

int	main(void)
{
	extern t_shell	g_shell;
	char	*line;
	char	*prompt;

	init_minishell();
	// set_sig_for_interactive_shell();
	g_shell.status = 129;
	while (1)
	{
		prompt = util_create_prompt_str();
		line = readline(prompt);
		free(prompt);
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		printf("line is [%s]\n", line);
		lexer(line);
		free(line);
	}
	ft_putstr_fd(UP_LINE_CURSOR, STDERR_FILENO);
	ft_putstr_fd(ADVANCE_CURSOR, STDERR_FILENO);
	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit(EXIT_SUCCESS);
}
