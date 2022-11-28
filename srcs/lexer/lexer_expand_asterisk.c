/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_asterisk.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 01:21:00 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/29 00:55:16 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			get_cwd_files_name(char ***files);
static void			sort_strarry(char **str_arry);
static t_each_str	*parse_split_each_str(char *src_str);
static void			new_token_add_back(t_token_info *info, size_t len);

void	expand_wildcard_asterisk(t_token_info *info)
{
	size_t		i;
	char		**files;
	char		*asterisk_str;
	t_each_str	*each_str;

	get_cwd_files_name(&files);
	sort_strarry(files);
	asterisk_str = ft_strdup(info->token->comp);
	if (!asterisk_str)
		util_put_cmd_err_and_exit("in expand_wildcard_asterisk");
	each_str = parse_split_each_str(asterisk_str);
	i = -1;
	while (files[++i])
	{
		if (is_wildcard_expandble(files[i], each_str))
		{
			new_token_add_back(info, ft_strlen(files[i]));
			ft_strlcpy(info->token->comp, files[i], ft_strlen(files[i]) + 1);
			info->each_i = ft_strlen(files[i]);
		}
	}
	remove_backslash(info->token->comp);
	free(asterisk_str);
	ft_safe_free_double_ptr((void ***)&files);
	del_each_str_list(each_str);
}

static void	get_cwd_files_name(char ***files)
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

static void	sort_strarry(char **str_arry)
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

static t_each_str	*parse_split_each_str(char *src_str)
{
	t_as_info	info;

	init_info(&info, src_str);
	while (src_str[info.str_i])
	{
		while (src_str[info.str_i] == '*')
		{
			info.str_i++;
			info.prev_as = true;
		}
		if (src_str[info.str_i] != '\0')
		{
			info.start_i = info.str_i;
			while (src_str[info.str_i] && (src_str[info.str_i] != '*'
					|| src_str[info.str_i - 1] == '\\'))
				info.str_i++;
			if (src_str[info.str_i] == '*')
				info.next_as = true;
			create_each_str_add_back(&info);
		}
	}
	return (info.res);
}

static void	new_token_add_back(t_token_info *info, size_t len)
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
