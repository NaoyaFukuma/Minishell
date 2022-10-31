/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_create_prompt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:43:44 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/31 12:24:04 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_and_free_err_exit(char *str1, bool free_str1, char *str2,
				bool free_str2);

char	*util_create_prompt_str(void)
{
	char			*ret_str;
	extern t_shell	g_shell;
	char			*tmp_str;

	if (g_shell.status == 0)
		ret_str = join_and_free_err_exit(DEFAULT_COLOR, false, "[", false);
	else if (0 < g_shell.status && g_shell.status < 128)
		ret_str = join_and_free_err_exit(RED_COLOR, false, "[", false);
	else
		ret_str = join_and_free_err_exit(YELLOW_COLOR, false, "[", false);
	tmp_str = ft_itoa(g_shell.status);
	if (!tmp_str)
		util_put_cmd_err_and_exit("in create_prompt_str");
	ret_str = join_and_free_err_exit(ret_str, true, tmp_str, true);
	ret_str = join_and_free_err_exit(ret_str, true, "] \e[m", false);
	ret_str = join_and_free_err_exit(ret_str, true, g_shell.pwd, false);
	ret_str = join_and_free_err_exit(ret_str, true, " > ", false);
	return (ret_str);
}

static char	*join_and_free_err_exit(char *str1, bool free_str1, char *str2,
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
