/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_put_err_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:11:05 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/21 13:17:14 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	util_put_err_exit(char *err_msg)
{
	ft_putstr_fd(RED_COLOR, STDERR_FILENO);
	perror(err_msg);
	ft_putstr_fd(WHITE_COLOR, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
