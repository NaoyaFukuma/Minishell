/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 01:03:46 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/26 16:36:48 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_builtin(char **args)
{
	if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args));
	if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args));
	if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env());
	// if (ft_strcmp(args[0], "export") == 0)
	// 	return (builtin_export(args));
	if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args));
	(void)args;
	return (EXIT_FAILURE);
}
