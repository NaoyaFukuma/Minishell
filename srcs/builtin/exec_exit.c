/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 01:05:56 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/23 02:32:22 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_num_args_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
}

static bool	has_error(char **args, int i)
{
	if (util_is_digit_str(args[i]))
	{
		put_num_args_error(args[i]);
		exit(255);
	}
	if (args[i + 1])
	{
		util_put_cmd_err("exit", "too many arguments");
		return (true);
	}
	return (false);
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
	status = ft_atoi(args[i]);
	if (has_error(args, i) == false)
		exit(status);
	g_shell.exited = true;
	return (EXIT_FAILURE);
}
