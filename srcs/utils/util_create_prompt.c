/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_create_prompt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:43:44 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/17 10:17:43 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*util_create_prompt_str(void)
{
	char			*str;
	extern t_shell	g_shell;

	str = join_free(GREEN, false, g_shell.pwd, false);
	if (g_shell.status == 0)
		str = join_free(str, true, "\e[m\e[37m", false);
	else
		str = join_free(str, true, "\e[m\e[31m", false);
	str = join_free(str, true, " > \e[m", false);
	g_shell.prompt_len = ft_strlen(str) - 16;
	return (str);
}

char	*join_free(char *str1, bool free_str1, char *str2, bool free_str2)
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
