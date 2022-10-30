/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_create_prompt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:43:44 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/30 21:54:58 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_and_free_err_exit(char *str1, bool free_str1, char *str2, bool free_str2);

char	*util_create_prompt_str(void)
{
	char	*ret_str;
	extern t_shell	g_shell;
	char	*status;

	status = ft_itoa(g_shell.status);
	if (!status)
		util_put_cmd_err_and_exit("in create_prompt_str");
	ret_str = join_and_free_err_exit("\n", false, status, true);
	ret_str = join_and_free_err_exit(ret_str, true, ":", false);
	ret_str = join_and_free_err_exit(ret_str, true, g_shell.pwd, false);
	if (g_shell.status == 0)
		;
	else if (0 < g_shell.status && g_shell.status < 128)
		ret_str = join_and_free_err_exit(ret_str, true, RED_COLOR, false);
	else
		ret_str = join_and_free_err_exit(ret_str, true, YELLOW_COLOR, false);
	ret_str = join_and_free_err_exit(ret_str, true, "\n> \e[m", false);
	return (ret_str);
}

static char	*join_and_free_err_exit(char *str1, bool free_str1, char *str2, bool free_str2)
{
	char	*ret_str;

	ret_str = ft_strjoin(str1, str2);
	if (!ret_str)
		util_put_cmd_err_and_exit("in create_prompt_str");
	if (free_str1 == true)
		free(str1);
	if (free_str2 == true)
		free(str2);
	return (ret_str);
}
