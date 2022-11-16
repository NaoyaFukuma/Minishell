/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 10:40:29 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/17 01:32:43 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_delete(char *name);

int	builtin_unset(char **args)
{
	extern t_shell	g_shell;
	int				status;

	status = EXIT_SUCCESS;
	while (*(++args))
	{
		if (util_validate_env_name(*args))
			env_delete(*args);
		else
		{
			util_put_env_name_error("unset", *args);
			status = EXIT_FAILURE;
		}
	}
	return (status);
}

static void	env_delete(char *name)
{
	extern t_shell	g_shell;
	t_env	*now;
	t_env	*prev;

	now = g_shell.envs;
	prev = NULL;
	while (now)
	{
		if (!ft_strcmp(now->name, name))
		{
			if (!prev)
				g_shell.envs = now->next;
			else
				prev->next = now->next;
			free(now->name);
			free(now->value);
			free(now);
			break ;
		}
		prev = now;
		now = now->next;
	}
}
