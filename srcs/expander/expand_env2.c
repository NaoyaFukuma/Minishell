/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:20:40 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/13 00:12:41 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	calc_len(char *str, char *esc_chars);
static void		add_esc_and_dup_val(char *src, char *esc_chars, char *dest);

char	*set_env_name(char *str)
{
	size_t	var_len;
	char	*res;

	if (*str == '?')
		return (ft_strdup("?"));
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
		res = ft_itoa(g_shell.status);
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

char	*create_esc_val(char *str, t_token_status state)
{
	char	*esc_chars;
	char	*res;

	if (state == D_QUOTED)
		esc_chars = "\"\\$*";
	if (state == NOT_QUOTED)
		esc_chars = "\'\"\\$|;><";
	res = malloc(sizeof(char *) * (calc_len(str, esc_chars) + 1));
	if (!res)
		util_put_cmd_err_and_exit("in create_esc_val");
	add_esc_and_dup_val(str, esc_chars, res);
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

static void	add_esc_and_dup_val(char *src, char *esc_chars, char *dst)
{
	size_t	i;

	i = 0;
	while (*src)
	{
		if (ft_strchr(esc_chars, *src))
			dst[i++] = '\\';
		dst[i++] = (*src++);
	}
	dst[i] = '\0';
}
