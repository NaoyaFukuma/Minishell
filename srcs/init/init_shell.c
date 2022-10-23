/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:19:44 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/23 15:41:55 by nfukuma          ###   ########.fr       */
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
		util_perror_and_exit("dup_envs");
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
	int				shlvl;

	env_shlvl = util_env_get("SHLVL");
	if (!util_is_digit_str(env_shlvl->value))
		shlvl = 0;
	else
		shlvl = ft_atoi(env_shlvl->value);
	free(env_shlvl->value);
	shlvl++;
	if (shlvl > 999)
	{
		env_shlvl->value = ft_itoa(shlvl);
		ft_putstr_fd("warning: shell level (1000) too high, resetting to 1\n",
				STDERR_FILENO);
	}
	else
		env_shlvl->value = ft_itoa(shlvl);
}

static void	print_env(t_env *envs)
{
	while (envs)
	{
		printf("%s=%s\n", envs->name, envs->value);
		envs = envs->next;
	}
}
