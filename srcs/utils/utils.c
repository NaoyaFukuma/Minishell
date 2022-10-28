/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 00:57:11 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/27 14:00:02 by nfukuma          ###   ########.fr       */
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

bool	util_is_directory(const char *path)
{
	t_stat path_stat;

	if (stat(path, &path_stat) == -1)
		return (false);
	if (S_ISDIR(path_stat.st_mode))
		return (true);
	return (false);
}

bool	util_is_same_dir(char *dir1, char *dir2)
{
	t_stat	stat_dir1;
	t_stat	stat_dir2;

	if (!dir1 || !dir2)
		return (false);
	if (stat(dir1, &stat_dir1)  == -1)
		return (false);
	if (stat(dir2, &stat_dir2)  == -1)
		return (false);
	if (stat_dir1.st_ino == stat_dir2.st_ino)
		return (true);
	return (false);
}
