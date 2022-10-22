/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 01:05:56 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/22 22:02:27 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	has_error(char **args, int index)
{
	if (errno || )
	{
		/* code */
	}

}

int	exec_exit(char	**args)
{
	extern t_shell	g_shell;
	int				i;
	int				status;

	if (g_shell.interactive == true)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	i = 1;
	if (args[i] && ft_strcmp(args[i], "--") == 0)
		i++;
	if (!args[i])
		exit(g_shell.status);
	errno = 0;
	status = ft_atoi(args[i]);
	if (has_error(args, i) == false)
		exit(status);
	g_shell.exited = true;
	return (EXIT_FAILURE);
}
