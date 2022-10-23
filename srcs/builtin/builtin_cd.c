/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:46:26 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/23 23:13:04 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	put_cd_err(char *dir, char *message);

int	builtin_cd(char **args)
{
	char	*dst_dir;
	extern t_shell	g_shell;

	if (!args[1])
	{
		if (!util_env_get("HOME"))
		{
			util_put_cmd_err("cd", "HOME not set");
			return (EXIT_FAILURE);
		}
		if (chdir(util_env_get("HOME")->value) == -1)
		{
			util_put_cmd_err("cd", strerror(errno));
			return (EXIT_FAILURE);
		}
		else
		{
			util_set_env("OLDPWD", util_env_get("PWD") ? util_env_get("PWD")->value : NULL, ENV_TRUNC);
			free()
		}
	}
	else
		dst_dir = args[1];



}

static void	put_cd_err(char *dir, char *message)
{
	ft_putstr_fd(RED_COLOR, STDERR_FILENO);
	ft_putstr_fd("minishell: cd:", STDERR_FILENO);
	ft_putstr_fd(dir, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	ft_putstr_fd(WHITE_COLOR, STDERR_FILENO);
}
