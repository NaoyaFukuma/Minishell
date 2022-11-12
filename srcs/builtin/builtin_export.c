/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:22:22 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/11 15:55:14 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_set_envs(char **args);
static void	sep_arg(char *arg, char **sep_posi, char **value,
				bool *append_flag);
static void	restore_arg(char *sep, bool append_flag);

int	builtin_export(char **args)
{
	if (args[1] == NULL)
		return (print_each_envs());
	else
		return (export_set_envs(args));
	return (EXIT_SUCCESS);
}

static int	export_set_envs(char **args)
{
	char	*sep_posi;
	char	*value;
	bool	append_flag;
	int		ret;

	ret = EXIT_SUCCESS;
	value = NULL;
	while (*(++args))
	{
		append_flag = false;
		sep_arg(*args, &sep_posi, &value, &append_flag);
		if (util_validate_env_name(*args))
			util_env_update_value(*args, value, true, append_flag);
		else
		{
			restore_arg(sep_posi, append_flag);
			util_put_env_name_error("export", *args);
			ret = EXIT_FAILURE;
		}
	}
	return (ret);
}

static void	sep_arg(char *arg, char **sep_posi, char **value, bool *append_flag)
{
	*sep_posi = ft_strchr(arg, '=');
	if (*sep_posi)
	{
		**sep_posi = '\0';
		if (*sep_posi != arg && *(*sep_posi - 1) == '+')
		{
			*(*sep_posi - 1) = '\0';
			*append_flag = true;
		}
		*value = *sep_posi + 1;
	}
	else
		*value = NULL;
}

static void	restore_arg(char *sep, bool append_flag)
{
	if (sep)
	{
		*sep = '=';
		if (append_flag == true)
			*(sep - 1) = '+';
	}
}
