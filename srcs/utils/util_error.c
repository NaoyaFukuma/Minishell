/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:11:05 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/27 17:54:43 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	util_put_cmd_err(char *command, char *message)
{
	ft_putstr_fd(RED_COLOR, STDERR_FILENO);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (command)
	{
		ft_putstr_fd(command, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(message, STDERR_FILENO);
	ft_putstr_fd(DEFAULT_COLOR, STDERR_FILENO);
}

void	util_put_cmd_err_and_exit(char *cmd)
{
	util_put_cmd_err(cmd, strerror(errno));
	exit(EXIT_FAILURE);
}

void	util_put_env_name_error(char *command, char *name)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}
