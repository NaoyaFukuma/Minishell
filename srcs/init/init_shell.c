/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:19:44 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/22 00:03:02 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*dup_envs(void);
static void		print_env(t_env *envs);
static void		shell_level_update(void);

void	init_minishell(void)
{
	extern t_shell	g_shell;

	g_shell.envs = dup_envs();
	if (!g_shell.envs)
		util_put_err_exit("dup_envs");
	//デバック用
	shell_level_update();
	print_env(g_shell.envs);
}

static t_env	*dup_envs(void)
{
	extern char	**environ;
	size_t		i;
	t_env		*envs;
	t_env		*tmp_env;

	envs = NULL;
	i = -1;
	while (environ[++i])
	{
		tmp_env = util_list_new_envnode(environ[i]);
		if (!tmp_env)
			return (NULL);
		util_list_add_last_new_envnode(&envs, tmp_env);
	}
	return (envs);
}

static void	shell_level_update(void)
{
	extern t_shell	g_shell;
	t_env			*env_shlvl;

	env_shlvl = util_env_get("SHLVL");
	if (*(env_shlvl->value) - '0' > 999)
	{
		*(env_shlvl->value) = *(env_shlvl->value) - *(env_shlvl->value) + 1;
		ft_putstr_fd("warning: shell level (1000) too high, resetting to 1\n", STDERR_FILENO);
	}
	else
		*(env_shlvl->value) = *(env_shlvl->value) + 1;
}

static void	print_env(t_env *envs)
{
	while (envs)
	{
		printf("%s=%s\n", envs->name, envs->value);
		envs = envs->next;
	}
}
