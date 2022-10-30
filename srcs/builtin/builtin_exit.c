/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 01:05:56 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/30 21:22:48 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_num_args_error(char *arg);
static bool	has_error(char **args, int i);

int	builtin_exit(char **args)
{
	extern t_shell	g_shell;
	int				i;

	if (g_shell.interactive == true)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	i = 1;
	if (args[i] && ft_strcmp(args[i], "--") == 0)
		i++;
	if (!args[i])
		exit(g_shell.status);
	if (has_error(args, i) == false)
		exit(ft_atoi(args[i]));
	g_shell.exited = true;
	return (EXIT_FAILURE);
}

static bool	has_error(char **args, int i)
{
	if (util_is_digit_str(args[i]) == false)
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

static void	put_num_args_error(char *arg)
{
	ft_putstr_fd("tsh: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
}
