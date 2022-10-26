/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:17:08 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/26 00:37:25 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*util_join_path(char *prv_path, char *nxt_path)
{
	char	*tmp;
	char	*return_path;
	size_t	index;

	if (!prv_path || !nxt_path)
		return (NULL);
	tmp = ft_strjoin(prv_path, "/");
	if (!tmp)
		util_put_cmd_err_and_exit(NULL);
	index = ft_strlen(tmp);
	if (index >= 2 && tmp[index - 2] == '/')
		tmp[index - 1] = '\0';
	return_path = ft_strjoin(tmp, nxt_path);
	if (!return_path)
		util_put_cmd_err_and_exit(NULL);
	free(tmp);
	return (return_path);
}

size_t	util_ptrarr_len(void **ptrarr)
{
	size_t	i;

	i = 0;
	while (ptrarr[i])
		i++;
	return (i);
}

void	**util_ptrarr_add_back(void **ptrarr, void *ptr)
{
	size_t	arr_size;
	void	**new_ptrarr;

	arr_size = 0;
	if (ptrarr)
		arr_size = ptrarr_len(ptrarr);
	new_ptrarr = ft_calloc(arr_size + 2, sizeof(void *));
	if (!new_ptrarr)
		return (NULL);
	ft_memcpy(new_ptrarr, ptrarr, sizeof(void *) * arr_size);
	new_ptrarr[arr_size] = ptr;
	return (new_ptrarr);
}

char	**util_colon_split(char *src_str, char *def)
{
	char	**res;
	char	**tmp;
	char	*next_index;

	res = NULL;
	next_index = ft_strchr(src_str, ':');
	while (next_index)
	{
		tmp = res;
		if (next_index - src_str == 0)
			res = util_ptrarr_add_back(res, ft_strdup(def));
		else
			res = util_ptrarr_add_back(res, ft_substr(src_str, 0, next_index
				- src_str));
		free(tmp);
		src_str = next_index + 1;
		next_index = ft_strchr(src_str, ':');
	}
	tmp = res;
	if (*src_str == '\0')
		res = util_ptrarr_add_back(res, ft_strdup(def));
	else
		res = util_ptrarr_add_back(res, ft_strdup(src_str));
	free(tmp);
	return ((char **)res);
}
