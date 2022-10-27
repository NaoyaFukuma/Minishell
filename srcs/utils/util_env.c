/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 23:30:56 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/26 14:48:38 by nfukuma          ###   ########.fr       */
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

static void	set_env_value(t_env *env, const char *new_value, bool append_flag)
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
	set_env_value(env, new_value, append_flag);
}


int	util_envs_print(t_env *envs)
{
	while (envs)
	{
		if (envs->is_env == true && envs->value != NULL)
			printf("%s=%s\n", envs->name, envs->value);
		envs = envs->next;
	}
	return (EXIT_SUCCESS);
}


