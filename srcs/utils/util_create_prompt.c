/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_create_prompt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:43:44 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/16 22:12:05 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*util_create_prompt_str(void)
{
	char			*ret_str;
	extern t_shell	g_shell;

	ret_str = util_join_and_free_err_exit(GREEN_COLOR, false, g_shell.pwd, false);
	if (g_shell.status == 0)
		ret_str = util_join_and_free_err_exit(ret_str, true, "\e[m""\e[37m", false);
	else
		ret_str = util_join_and_free_err_exit(ret_str, true, "\e[m""\e[31m", false);
	ret_str = util_join_and_free_err_exit(ret_str, true, " > \e[m", false);
	g_shell.prompt_len = ft_strlen(ret_str) - 16;
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
