/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:46:50 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/23 16:22:44 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*util_list_new_envnode(char *env_str)
{
	t_env	*env;
	char	*sep_ptr;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	sep_ptr = ft_strchr(env_str, '=');
	if (!sep_ptr)
	{
		env->name = ft_strdup(env_str);
		if (!env->name)
			return (NULL);
		env->next = NULL;
	}
	else
	{
		env->name = ft_substr(env_str, 0, sep_ptr - env_str);
		env->value = ft_strdup(sep_ptr + 1);
		if (!env->name || !env->value)
			return (NULL);
	}
	env->is_env = true;
	env->next = NULL;
	return (env);
}

t_env	*util_list_get_last_envnode(t_env *node_ptr)
{
	while (node_ptr->next)
		node_ptr = node_ptr->next;
	return (node_ptr);
}

void	util_list_add_last_new_envnode(t_env **envs, t_env *new_env)
{
	if (!envs || !new_env)
		return ;
	if (!*envs)
		*envs = new_env;
	else
		util_list_get_last_envnode(*envs)->next = new_env;
}
