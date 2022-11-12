/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_path_canonical.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 01:19:59 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/12 23:37:57 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cpy_path_elem(char *path_p, char *elem, char *start)
{
	if (ft_strcmp(elem, "..") == 0)
	{
		path_p = ft_strrchr(start, '/');
		if (!path_p)
			path_p = start;
		*path_p = '\0';
	}
	else if (ft_strcmp(elem, ".") != 0)
	{
		path_p = ft_strcpy_forward(path_p, "/");
		path_p = ft_strcpy_forward(path_p, elem);
	}
	return (path_p);
}

void	add_slash_path_front(char *path, char **res)
{
	char	*added_res;

	if (!path || !res || !*res)
		return ;
	if (ft_strncmp(path, "//", 2) == 0 && path[2] != '/' &&
		ft_strncmp(*res, "//", 2) != 0)
	{
		if (!(added_res = ft_strjoin("/", *res)))
			util_put_cmd_err_and_exit(NULL);
		ft_safe_free_single_ptr((void **)res);
		*res = added_res;
	}
}

bool	cpy_canonical_path(char **split, char **res)
{
	char	*start;
	char	*path_p;
	size_t	i;

	start = *res;
	*start = '\0';
	i = 0;
	path_p = start;
	while (split[i])
	{
		path_p = cpy_path_elem(path_p, split[i], start);
		if (path_p == start)
			path_p = ft_strcpy_forward(path_p, "/");
		if (!util_is_directory(start))
			return (false);
		i++;
	}
	if (path_p == start)
		path_p = ft_strcpy_forward(path_p, "/");
	return (true);
}

char	*util_path_canonical(char *path)
{
	char	**split;
	char	*res;

	if (!path)
		return (NULL);
	split = ft_split(path, '/');
	res = malloc(sizeof(char *) * (ft_strlen(path) + 1));
	if (!split || !res)
		util_put_cmd_err_and_exit(NULL);
	if (!cpy_canonical_path(split, &res))
		ft_safe_free_single_ptr((void **)&res);
	ft_safe_free_double_ptr((void ***)&split);
	add_slash_path_front(path, &res);
	return (res);
}
