/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_asterisk.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 01:21:00 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/16 11:30:03 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_strarry(char **str_arry)
{
	size_t	i;
	char	*swap_ptr;

	i = 0;
	while (str_arry[i])
	{
		if (str_arry[i + 1] && 0 < ft_strcmp(str_arry[i], str_arry[i + 1]))
		{
			swap_ptr = str_arry[i + 1];
			str_arry[i + 1] = str_arry[i];
			str_arry[i] = swap_ptr;
			i = 0;
			continue ;
		}
		i++;
	}
}

bool	is_wildcard_expandble(char *asterisk_str, char *str)
{
	bool	wildcard_flag;

	wildcard_flag = false;
	while (1)
	{
		while (*asterisk_str == '*')
		{
			if (*(++asterisk_str) == '\0')
				return (true);
			wildcard_flag = true;
		}
		if (wildcard_flag)
		{
			str = ft_strrchr(str, *asterisk_str);
			if (!str++)
				return (false);
			wildcard_flag = false;
		}
		if ((*str)++ != (*asterisk_str)++)
			return (false);
		if (*str == '\0' && *asterisk_str == '\0')
			return (true);
	}
}

void	get_cwd_files_name(char ***files)
{
	DIR				*dir;
	struct dirent	*dir_p;
	char			*tmp;

	tmp = getcwd(NULL, 0);
	if (!tmp)
		util_put_cmd_err_and_exit("in expand_wildcard_asterisk");
	dir = opendir(tmp);
	if (!dir)
		util_put_cmd_err_and_exit("in expand_wildcard_asterisk");
	free(tmp);
	*files = NULL;
	dir_p = readdir(dir);
	while (dir_p)
	{
		if (dir_p->d_name[0] != '.')
		{
			tmp = ft_strdup(dir_p->d_name);
			if (!tmp)
				util_put_cmd_err_and_exit("in expand_wildcard_asterisk");
			*files = (char **)util_ptrarr_add_back((void **)*files,
													(void *)tmp);
		}
		dir_p = readdir(dir);
	}
}

void	new_token_add_back(t_token_info *info, size_t len)
{
	if (is_containing_asterisk(info))
	{
		if (info->token->prev)
		{
			info->token = info->token->prev;
			del_token(&info->token->next);
			info->token->next = init_token(info->token, len);
			info->token = info->token->next;
		}
		else
		{
			del_token(&info->token);
			info->token = init_token(info->token, len);
			info->first_token = info->token;
		}
	}
	else
	{
		info->token->next = init_token(info->token, len);
		info->token = info->token->next;
	}
}

void	expand_wildcard_asterisk(t_token_info *info)
{
	size_t	i;
	char	**cwd_files;
	char	*asterisk_str;

	get_cwd_files_name(&cwd_files);
	sort_strarry(cwd_files);
	asterisk_str = ft_strdup(info->token->comp);
	if (!asterisk_str)
		util_put_cmd_err_and_exit("in expand_wildcard_asterisk");
	i = -1;
	while (cwd_files[++i])
	{
		if (is_wildcard_expandble(asterisk_str, cwd_files[i]))
		{
			new_token_add_back(info, ft_strlen(cwd_files[i]));
			ft_strlcpy(info->token->comp, cwd_files[i], ft_strlen(cwd_files[i])
					+ 1);
			info->each_i = ft_strlen(cwd_files[i]);
		}
	}
	free(asterisk_str);
	ft_safe_free_double_ptr((void ***)&cwd_files);
}
