/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 00:57:11 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/22 01:18:27 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	util_is_builtin(const char *arg)
{
	const char	*builtin_cmd[] = { "exit", "cd", "echo", "pwd", "env", "export", "unset",
		NULL};
	int			i;

	if (!arg)
		return (false);
	i = -1;
	while (builtin_cmd[++i])
		if (ft_strcmp(arg, builtin_cmd[i]))
			return (true);
	return (false);
}
