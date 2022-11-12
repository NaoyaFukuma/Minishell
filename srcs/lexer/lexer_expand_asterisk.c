/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_asterisk.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 01:21:00 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/12 23:11:21 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_containing_asterisk(t_token_info *info)
{
	size_t	i;

	if (!info || !info->token || !info->token->comp ||
		info->each_i == 0)
		return (false);
	i = -1;
	while (++i <= info->each_i)
	{
		if (info->token->comp[i] == '*')
		{
			if (info->esc_flag && i > 0 && info->token->comp[i - 1] == '\\')
			{
				ft_memmove(&info->token->comp[i - 1], &info->token->comp[i],
						info->each_i - i);
				info->token->comp[info->each_i - 1] = '\0';
				return (false);
			}
			info->token->comp[info->each_i] = '\0';
			return (true);
		}
	}
	return (false);
}

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
	size_t	i;
	bool	wildcard_flag;
	char	*tmp;

	i = 0;
	wildcard_flag = false;
	while (1)
	{
		while (asterisk_str[i] == '*')
		{
			i++;
			if (!asterisk_str[i])
				return (true);
			wildcard_flag = true;
		}
		if (wildcard_flag)
		{
			tmp = ft_strrchr(str, asterisk_str[i]);
			if (!tmp)
				return (false);
			else
			{
				str = tmp + 1;
				i++;
				wildcard_flag = false;
			}
		}
		else
		{
			if (*str == asterisk_str[i])
			{
				str++;
				i++;
			}
			else
				return (false);
		}
		if (!asterisk_str[i] && !*str)
			return (true);
	}
}

void	expand_wildcard_asterisk(t_token_info *info)
{
	char			*cwd;
	DIR				*dir;
	struct dirent	*dir_p;
	char			**cwd_files;
	char			*tmp_file_name;
	size_t			i;
	char			*asterisk_str;

	asterisk_str = ft_strdup(info->token->comp);
	if (!asterisk_str)
		util_put_cmd_err_and_exit("in expand_wildcard_asterisk");
	cwd = getcwd(NULL, 0);
	if (!cwd)
		util_put_cmd_err_and_exit("in expand_wildcard_asterisk");
	dir = opendir(cwd);
	if (!dir)
		util_put_cmd_err_and_exit("in expand_wildcard_asterisk");
	cwd_files = NULL;
	while (1)
	{
		dir_p = readdir(dir);
		if (!dir_p)
			break ;
		if (!(dir_p->d_name[0] == '.'))
		{
			tmp_file_name = ft_strdup(dir_p->d_name);
			if (!tmp_file_name)
				util_put_cmd_err_and_exit("in expand_wildcard_asterisk");
			cwd_files = (char **)util_ptrarr_add_back((void **)cwd_files,
					(void *)tmp_file_name);
		}
	}
	sort_strarry(cwd_files);
	i = -1;
	while (cwd_files[++i])
	{
		if (is_wildcard_expandble(asterisk_str, cwd_files[i]))
		{
			if (is_containing_asterisk(info))
			{
				if (info->token->prev)
				{
					info->token = info->token->prev;
					del_token(&info->token->next);
					info->token->next = init_token(info->token,
							ft_strlen(cwd_files[i]));
					info->token = info->token->next;
				}
				else
				{
					del_token(&info->token);
					info->token = init_token(info->token,
							ft_strlen(cwd_files[i]));
					info->first_token = info->token;
				}
			}
			else
			{
				info->token->next = init_token(info->token,
						ft_strlen(cwd_files[i]));
				info->token = info->token->next;
			}
			ft_strlcpy(info->token->comp, cwd_files[i], ft_strlen(cwd_files[i])
					+ 1);
			info->each_i = ft_strlen(cwd_files[i]);
		}
		// printf("is_wildcard_expandble = %s\n", cwd_files[i]);
	}
	printf("\n");
	// for (size_t i = 0; cwd_files[i]; i++)
	// {
	// 	printf("cwd_files[%zu] == %s\n", i, cwd_files[i]);
	// }
	free(asterisk_str);
	ft_safe_free_double_ptr((void ***)&cwd_files);
	free(cwd);
}
