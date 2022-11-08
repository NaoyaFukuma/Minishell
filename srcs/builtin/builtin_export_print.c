/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:20:24 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/08 15:08:30 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		print_each_env(t_env *env);
static char		*create_esc_val_for_exp(char *str);
static size_t	calc_len(const char *str, const char *esc_chars);
static void		add_esc_and_dup_val(char *src, char *esc_chars, char *dst);

int	print_each_envs(void)
{
	extern t_shell	g_shell;
	t_env			*envs_list_ptr;
	t_env			*tmp_ptr;

	envs_list_ptr = util_copy_envs(g_shell.envs);
	env_sort_for_export(&envs_list_ptr);
	while (envs_list_ptr)
	{
		print_each_env(envs_list_ptr);
		tmp_ptr = envs_list_ptr->next;
		free(envs_list_ptr);
		envs_list_ptr = tmp_ptr;
	}
	return (EXIT_SUCCESS);
}

static void	print_each_env(t_env *env)
{
	char	*escaped_value;

	if (env->is_env == false)
		return ;
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(env->name, STDOUT_FILENO);
	if (env->value)
	{
		escaped_value = create_esc_val_for_exp(env->value);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(escaped_value, STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
		free(escaped_value);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static char	*create_esc_val_for_exp(char *str)
{
	char	*esc_chars;
	char	*res;

	esc_chars = "\"\\$`";
	res = malloc(sizeof(char *) * (calc_len(str, esc_chars) + 1));
	if (!res)
		util_put_cmd_err_and_exit("in create_esc_val_for_exp");
	add_esc_and_dup_val(str, esc_chars, res);
	return (res);
}

static size_t	calc_len(const char *str, const char *esc_chars)
{
	size_t	res;

	res = 0;
	while (*str)
	{
		if (ft_strchr(esc_chars, *str))
			res++;
		res++;
		str++;
	}
	return (res);
}

static void	add_esc_and_dup_val(char *src, char *esc_chars, char *dst)
{
	size_t	i;

	i = 0;
	while (*src)
	{
		if (ft_strchr(esc_chars, *src))
		{
			dst[i] = '\\';
			i++;
		}
		dst[i] = *src;
		i++;
		src++;
	}
	dst[i] = '\0';
}
