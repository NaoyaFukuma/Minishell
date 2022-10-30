/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:20:24 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/30 21:24:20 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_print_env(t_env *env);
static int	compare_env(t_env *left, t_env *right);

int	export_print_envs(void)
{
	extern t_shell	g_shell;
	t_env			*envs_list_ptr;
	t_env			*tmp_ptr;

	envs_list_ptr = util_copy_envs(g_shell.envs);
	env_mergesort(&envs_list_ptr, compare_env);
	while (envs_list_ptr)
	{
		export_print_env(envs_list_ptr);
		tmp_ptr = envs_list_ptr->next;
		free(envs_list_ptr);
		envs_list_ptr = tmp_ptr;
	}
	return (EXIT_SUCCESS);
}

static int	compare_env(t_env *left, t_env *right)
{
	return (ft_strcmp(left->name, right->name));
}

static void	export_print_env(t_env *env)
{
	char	*escaped_value;

	if (env->is_env == false)
		return ;
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(env->name, STDOUT_FILENO);
	if (env->value)
	{
		// escaped_value = create_expanded_str(env->value, D_QUOTED, true);
		escaped_value = env->value;
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(escaped_value, STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
		free(escaped_value);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}
