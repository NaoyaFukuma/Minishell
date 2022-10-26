/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 10:40:29 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/26 16:30:29 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_env_name_error(char *command, char *name);
static bool	validate_env_name(char *name);

void	env_delete(char *name)
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

int	builtin_unset(char **args)
{
	extern t_shell	g_shell;
	int				status;

	status = EXIT_SUCCESS;
	while (++args)
	{
		if (validate_env_name(*args))
			env_delete(*args);
		else
		{
			put_env_name_error("unset", *args);
			status = EXIT_FAILURE;
		}
	}
	return (status);
}

static bool	validate_env_name(char *name)
{
	size_t i;

	i = 0;
	if (name[i] != '_' && !ft_isalpha(name[i]))
		return (false);
	while (name[++i])
		if (name[i] != '_' && !ft_isalnum(name[i]))
			return (false);
	return (true);
}

static void	put_env_name_error(char *command, char *name)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}
