/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 00:57:11 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/23 01:42:58 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	util_is_builtin(const char *arg)
{
	const char	*builtin_cmd[] = { "exit", "cd", "echo", "pwd", "env", "export", "unset",
		NULL};
	int			i;

	if (!arg)
		return (false);
	i = -1;
	while (builtin_cmd[++i])
		if (ft_strcmp(arg, builtin_cmd[i]))
			return (true);
	return (false);
}

bool	util_is_digit_str(const char *str)
{
	size_t	i;
	bool	has_digit;

	i = 0;
	has_digit = false;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			has_digit = true;
		else
			break ;
		i++;
	}
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\0' && has_digit == true)
		return (true);
	else
		return (false);
}
