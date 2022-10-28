/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:43:48 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/27 14:18:48 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pwd(void)
{
	extern t_shell	g_shell;
	t_env			*pwd_env;

	pwd_env = util_env_get("PWD");
	if (!pwd_env)
	{
		pwd_env = util_list_new_envnode("PWD");
		if (!pwd_env)
			util_put_cmd_err_and_exit("malloc in init_pwd");
		util_list_add_last_new_envnode(&g_shell.envs, pwd_env);
	}
	g_shell.pwd = getcwd(NULL, 0);
	if (!g_shell.pwd)
		util_put_cmd_err_and_exit("getcwd in pwdinit");
	if (!pwd_env->value || !util_is_same_dir(pwd_env->value, g_shell.pwd))
	{
		free(pwd_env->value);
		pwd_env->value = ft_strdup(g_shell.pwd);
		if (!pwd_env->value)
			util_put_cmd_err_and_exit("malloc in init_pwd");
	}
}

void	init_oldpwd(void)
{
	extern t_shell	g_shell;
	t_env			*oldpwd_env;

	oldpwd_env = util_env_get("OLDPWD");
	if (!oldpwd_env)
	{
		oldpwd_env = util_list_new_envnode("OLDPWD");
		if (!oldpwd_env)
			util_put_cmd_err_and_exit("malloc in init_pwd");
		util_list_add_last_new_envnode(&g_shell.envs, oldpwd_env);
	}
}

