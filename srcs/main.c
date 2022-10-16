#include "../includes/minishell.h"

int	main(void)
{
	char	*line;

	line = NULL;
	while (line)
	{
		line = readline("tsh > ");
		if (line == NULL)
			break ;
		printf("line is [%s]\n", line);
		free(line);
	}
	write(1, "exit\n", 5);
	return (0);
}
