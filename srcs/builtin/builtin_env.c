/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 10:28:32 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/28 22:53:39 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	envs_print(t_env *envs);

int	builtin_env(void)
{
	extern t_shell	g_shell;

	envs_print(g_shell.envs);
	return (EXIT_SUCCESS);
}

static int	envs_print(t_env *envs)
{
	while (envs)
	{
		if (envs->is_env == true && envs->value != NULL)
			printf("%s=%s\n", envs->name, envs->value);
		envs = envs->next;
	}
	return (EXIT_SUCCESS);
}
