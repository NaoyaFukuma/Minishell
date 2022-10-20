/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:28:01 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/19 21:59:37 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strcat_and_free(char **text, char **buf, size_t len)
{
	char	*catstr;
	size_t	i;
	size_t	j;

	catstr = malloc(len + 1);
	if (catstr == NULL)
	{
		free(*buf);
		*buf = NULL;
		return (NULL);
	}
	i = -1;
	while ((*text)[++i] != '\0')
		catstr[i] = (*text)[i];
	j = -1;
	while ((*buf)[++j] != '\0')
		catstr[j + i] = (*buf)[j];
	catstr[j + i] = '\0';
	free(*text);
	*text = NULL;
	free(*buf);
	*buf = NULL;
	return (catstr);
}

char	*ft_delete_one_strage(t_gnl_list **static_p, t_gnl_list **lst_p)
{
	if ((*static_p)->next == NULL)
		(*static_p) = NULL;
	else if ((*lst_p)->previous == NULL)
	{
		(*static_p) = (*lst_p)->next;
		(*static_p)->previous = NULL;
	}
	else if ((*lst_p)->next == NULL)
		(*lst_p)->previous->next = NULL;
	else
	{
		(*lst_p)->previous->next = (*lst_p)->next;
		(*lst_p)->next->previous = (*lst_p)->previous;
	}
	free((*lst_p)->text);
	free(*lst_p);
	return (NULL);
}

char	*ft_push_end_line(t_gnl_list **lst_p)
{
	char	*newline;
	size_t	i;

	newline = malloc((*lst_p)->text_len + 1);
	if (newline == NULL)
		return (NULL);
	i = -1;
	while ((*lst_p)->text[++i] != '\0')
		newline[i] = (*lst_p)->text[i];
	newline[i] = '\0';
	free((*lst_p)->text);
	(*lst_p)->text = NULL;
	(*lst_p)->text_len = 0;
	return (newline);
}

char	*ft_parse_readsize(ssize_t readsize, char **buf, t_gnl_list **lst_p,
		t_gnl_list **static_p)
{
	free(*buf);
	*buf = NULL;
	if (readsize == -1)
		return (NULL);
	if ((*lst_p)->text_len == 0)
		return (ft_delete_one_strage(static_p, lst_p));
	(*lst_p)->fin_flag = 1;
	return (ft_push_end_line(&(*lst_p)));
}

char	*ft_read_file_push_line(t_gnl_list **lst_p, t_gnl_list **static_p)
{
	char	*buf;
	char	*catstr;
	ssize_t	readsize;

	while (1)
	{
		buf = malloc((size_t)BUFFER_SIZE + 1);
		if (buf == NULL)
			return (NULL);
		readsize = read((*lst_p)->fd, buf, BUFFER_SIZE);
		if (readsize == 0 || readsize == -1)
			return (ft_parse_readsize(readsize, &buf, lst_p, static_p));
		buf[readsize] = '\0';
		if ((size_t)readsize < (size_t)BUFFER_SIZE)
			(*lst_p)->fin_flag = 1;
		catstr = ft_strcat_and_free(&((*lst_p)->text), &buf, (*lst_p)->text_len
				+ readsize);
		if (catstr == NULL)
			return (NULL);
		(*lst_p)->text = catstr;
		if (ft_strchar((*lst_p)->text, '\n'))
			return (ft_split_and_store_text((*lst_p)->text, (*lst_p)->text_len
					+ readsize, *lst_p));
		(*lst_p)->text_len = (*lst_p)->text_len + readsize;
	}
}
