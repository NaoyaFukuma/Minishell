/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 10:37:08 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/24 10:39:59 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_pwd(void)
{
	extern t_shell	g_shell;

	ft_putendl_fd(util_env_get("PWD")->value, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
