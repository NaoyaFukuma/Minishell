/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_create_prompt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:43:44 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/12 23:48:57 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*util_create_prompt_str(void)
{
	char			*ret_str;
	extern t_shell	g_shell;
	char			*tmp_str;

	if (g_shell.status == 0)
		ret_str = util_join_and_free_err_exit("\n", false, WHITE_COLOR, false);
	else if (0 < g_shell.status && g_shell.status < 128)
		ret_str = util_join_and_free_err_exit("\n", false, RED_COLOR, false);
	else
		ret_str = util_join_and_free_err_exit("\n", false, YELLOW_COLOR, false);
	tmp_str = ft_itoa(g_shell.status);
	if (!tmp_str)
		util_put_cmd_err_and_exit("in create_prompt_str");
	ret_str = util_join_and_free_err_exit(ret_str, true, "[", false);
	ret_str = util_join_and_free_err_exit(ret_str, true, tmp_str, true);
	ret_str = util_join_and_free_err_exit(ret_str, true, "] \e[m\e[32m", false);
	ret_str = util_join_and_free_err_exit(ret_str, true, g_shell.pwd, false);
	ret_str = util_join_and_free_err_exit(ret_str, true, " > \e[m", false);
	g_shell.prompt_len = ft_strlen(ret_str) - 9;
	return (ret_str);
}

char	*util_join_and_free_err_exit(char *str1, bool free_str1, char *str2,
		bool free_str2)
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
