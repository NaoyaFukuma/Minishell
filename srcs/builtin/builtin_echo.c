/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 09:52:08 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/24 10:29:02 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	is_echo_option(char *arg);

int	builtin_echo(char **args)
{
	size_t	i;
	bool	option_flag;

	i = 0;
	option_flag = false;
	while (args[++i])
	{
		if (is_echo_option(args[i]))
			option_flag = true;
		else
			break ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (option_flag == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

static bool	is_echo_option(char *arg)
{
	if (!arg || ft_strlen(arg) < 2)
		return (false);
	if (arg[0] == '-')
	{
		arg++;
		while (*arg == 'n')
			arg++;
		if (*arg == '\0')
			return (true);
	}
	return (false);
}
