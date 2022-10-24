/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 10:28:32 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/24 10:34:37 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	print_env(t_env *envs);

int	builtin_env(void)
{
	extern t_shell	g_shell;

	print_env(g_shell.envs);
	return (EXIT_SUCCESS);
}

static void	print_env(t_env *envs)
{
	while (envs)
	{
		if (envs->is_env == true && envs->value != NULL)
			printf("%s=%s\n", envs->name, envs->value);
		envs = envs->next;
	}
}
