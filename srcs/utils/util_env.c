/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 23:30:56 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/23 23:43:01 by nfukuma          ###   ########.fr       */
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

util_set_env(const char *name, const char *value, int mode)
{
	t_env	*target_env;
	char	*tmp_env_str;

	target_env = util_env_get(name);
	if (!target_env)
	{
		if (!value)
			target_env = util_list_new_envnode(name);
		else
		{
			tmp_env_str = ft_calloc((ft_strlen(name) + ft_strlen(value) + 2), 1);
			if (!tmp_env_str)
				util_perror_and_exit("malloc");
			ft_strlcpy(tmp_env_str, name, ft_strlen(name));
			ft_strlcpy(tmp_env_str + ft_strlen(name), "=", 1);
			ft_strlcpy(tmp_env_str + ft_strlen(name) + 1, value, ft_strlen(value));

			tmp_env_str = ft_strjoin(tmp_env_str, "=");

			free(tmp_env_str);
		}

	}

}
