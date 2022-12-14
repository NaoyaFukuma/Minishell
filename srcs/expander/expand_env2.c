/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:20:40 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/25 22:42:39 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	calc_len(char *str, char *esc_chars);
static void		add_esc_and_dup_val(char *src, char *esc_chars, char *dest,
					t_expander *exper);

char	*set_env_name(char *str)
{
	size_t	var_len;
	char	*res;

	if (*str == '?')
	{
		res = ft_strdup("?");
		if (!res)
			util_put_cmd_err_and_exit("in set_env_name");
		return (res);
	}
	var_len = 0;
	if (ft_isdigit(*str))
	{
		res = ft_strdup("");
		if (!res)
			util_put_cmd_err_and_exit("in set_env_name");
		return (res);
	}
	while (ft_isalnum(str[var_len]) || str[var_len] == '_')
		var_len++;
	res = malloc(sizeof(char) * var_len + 1);
	if (!res)
		util_put_cmd_err_and_exit("in set_env_name");
	ft_strlcpy(res, str, var_len + 1);
	return (res);
}

char	*set_env_value(char *name)
{
	char			*res;
	extern t_shell	g_shell;

	if (ft_strcmp("?", name) == 0)
	{
		res = ft_itoa((int)g_shell.status);
		if (!res)
			util_put_cmd_err_and_exit("set_env_value");
	}
	else
	{
		if (!util_env_get(name) || !util_env_get(name)->value)
			res = ft_strdup("");
		else
			res = ft_strdup(util_env_get(name)->value);
		if (!res)
			util_put_cmd_err_and_exit("set_env_value");
	}
	return (res);
}

char	*create_esc_val(char *str, t_expander *exper)
{
	char	*esc_chars;
	char	*res;
	size_t	len;

	if (exper->status == D_QUOTED)
		esc_chars = "\"\\$*";
	if (exper->status == NOT_QUOTED)
		esc_chars = "\'\"\\$|;><";
	len = calc_len(str, esc_chars);
	if (exper->ex_flag)
		len += 2;
	res = malloc(sizeof(char *) * (len + 1));
	if (!res)
		util_put_cmd_err_and_exit("in create_esc_val");
	add_esc_and_dup_val(str, esc_chars, res, exper);
	return (res);
}

static size_t	calc_len(char *str, char *esc_chars)
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

static void	add_esc_and_dup_val(char *src, char *esc_chars, char *dst,
		t_expander *exper)
{
	size_t	i;

	i = 0;
	if (exper->ex_flag)
		dst[i++] = '"';
	while (*src)
	{
		if (ft_strchr(esc_chars, *src))
			dst[i++] = '\\';
		dst[i++] = (*src++);
	}
	if (exper->ex_flag)
		dst[i++] = '"';
	dst[i] = '\0';
}
