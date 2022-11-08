/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 23:30:56 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/08 16:05:38 by nfukuma          ###   ########.fr       */
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
		if (!ft_strcmp(env_ptr->name, name))
			return (env_ptr);
		env_ptr = env_ptr->next;
	}
	return (NULL);
}

static void	env_value_set(t_env *env, const char *new_value, bool append_flag)
{
	char	*old_value;

	old_value = env->value;
	if (append_flag == true)
	{
		if (old_value || new_value)
		{
			env->value = ft_strjoin(old_value, new_value);
			if (!env->value)
				util_put_cmd_err_and_exit(NULL);
		}
		else
			env->value = NULL;
	}
	else
	{
		if (new_value)
		{
			env->value = ft_strdup(new_value);
			if (!env->value)
				util_put_cmd_err_and_exit(NULL);
		}
		else
			env->value = NULL;
	}
	ft_safe_free_single_ptr((void *)&old_value);
}

void		util_env_update_value(const char *env_name, const char *new_value, bool is_env_var, bool append_flag)
{
	extern t_shell	g_shell;
	t_env			*env;

	if (!env_name)
		return ;
	env = util_env_get(env_name);
	if (!env)
	{
		env = util_list_new_envnode((char *)env_name);
		env->is_env = is_env_var;
		util_list_add_last_new_envnode(&g_shell.envs, env);
	}
	else
	{
		if (env->is_env == false)
			env->is_env = is_env_var;
		if (!new_value)
			return ;
	}
	env_value_set(env, new_value, append_flag);
}

bool	util_validate_env_name(char *name)
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

t_env	*util_copy_envs(t_env *envs_list)
{
	t_env	*res_list;
	t_env	*now_env;
	t_env	*copy_env;

	now_env = envs_list;
	res_list = NULL;
	while (now_env)
	{
		copy_env = malloc(sizeof(t_env));
		if (!copy_env)
			util_put_cmd_err_and_exit("malloc in util_copy_envs");
		copy_env->name = now_env->name;
		copy_env->value = now_env->value;
		copy_env->is_env = now_env->is_env;
		copy_env->next = NULL;
		util_list_add_last_new_envnode(&res_list, copy_env);
		now_env = now_env->next;
	}
	return (res_list);
}
