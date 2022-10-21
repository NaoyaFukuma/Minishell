/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 23:30:56 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/21 23:41:52 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*util_env_get(const	char *name)
{
	t_env	*env_ptr;
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
