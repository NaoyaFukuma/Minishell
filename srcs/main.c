#include "minishell.h"

t_shell	g_shell;

void	exe_cmd(char *str)
{
	extern char	**environ;
	pid_t	pid;
	int		status;
	char	**argv = malloc(sizeof(char *) * 2);

	argv[0] = str;
	argv[1] = NULL;

	if (!access(str, 1))
	{
		pid = fork();
		if (pid == 0)
		{
			printf("hoge\n");
			//未実装
			execve(str, argv, environ);
		}
		if (waitpid(pid, &status, 0) == -1)
		{
			//未実装
			printf("waitpid\n");
		}
		printf("exit_status : %d\n", status);
		printf("exit_status : %d\n", WEXITSTATUS(status));
		status = 1000;
		printf("exit_status : %d\n", status);
		printf("exit_status : %d\n", WEXITSTATUS(status));

	}
	//printf("%s\n", environ[0]);
}

int	main(void)
{
	char	*line;

	init_minishell();
	line = NULL;
	while (1)
	{
		line = readline("tsh > ");
		if (line == NULL)
			break ;
		printf("line is [%s]\n", line);
		exe_cmd(line);
		free(line);
	}
	ft_putstr_fd("libft test\n", STDOUT_FILENO);
	write(1, "exit\n", 5);
	return (0);
}
