/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 01:03:46 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/22 01:17:12 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_builtin(char **args)
{
	if (ft_strcmp(args[0], "exit") == 0)
		return (exec_exit(args));
	if (ft_strcmp(args[0], "cd") == 0)
		return (exec_cd(args));
	if (ft_strcmp(args[0], "echo") == 0)
		return (exec_echo(args));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (exec_pwd());
	if (ft_strcmp(args[0], "env") == 0)
		return (exec_env());
	if (ft_strcmp(args[0], "export") == 0)
		return (exec_export(args));
	if (ft_strcmp(args[0], "unset") == 0)
		return (exec_unset(args));
	return (EXIT_FAILURE);
}
