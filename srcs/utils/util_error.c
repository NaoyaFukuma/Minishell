/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:11:05 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/23 22:35:32 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	util_perror_and_exit(char *cmd)
{
	ft_putstr_fd(RED_COLOR, STDERR_FILENO);
	perror(cmd);
	ft_putstr_fd(WHITE_COLOR, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

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
	ft_putstr_fd(WHITE_COLOR, STDERR_FILENO);
}
