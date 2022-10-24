/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 23:30:56 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/24 00:50:40 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*util_env_get(const char *name)
{
	t_env			*env_ptr;
	extern t_shell	g_shell;

	if (!name)
		return (NULL);
	env_ptr = g_shell.envs;
	while (env_ptr)
	{
		if (!ft_strncmp(env_ptr->name, name, ft_strlen(name)))
			return (env_ptr);
		env_ptr = env_ptr->next;
	}
	return (NULL);
}

void	util_env_set(const char *target_name, const char *value, int mode)
{
	extern t_shell	g_shell;
	t_env	*target_env;
	char	*tmp_env_str;
	char	*tmp_value;

	target_env = util_env_get(target_name);
	if (!target_env)
	{
		target_env = malloc(sizeof(t_env));
		if (!target_env)
			util_perror_and_exit("malloc");
		target_env->name = target_name;
		target_env->value = value;
	}
	else
	{
		if (mode == ENV_TRUNC)
			target_env->value = value;
		else
		{
			tmp_value = target_env->value;
			target_env->value = ft_strjoin(tmp_value, value);
			free(tmp_value);
			free(value);
		}
	}
	util_list_add_last_new_envnode(g_shell.envs, target_env);
}
