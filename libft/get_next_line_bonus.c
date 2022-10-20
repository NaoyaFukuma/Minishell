/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:18:05 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/19 21:58:37 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_split_and_store_text(char *str, size_t strlen, t_gnl_list *lst_p)
{
	char	*newline;
	char	*tmp_str;
	size_t	i;
	size_t	j;

	newline = malloc(ft_strchar(str, '\n') - str + 2);
	if (newline == NULL)
		return (NULL);
	i = -1;
	while (++i < ft_strchar(str, '\n') - str + (size_t)1)
		newline[i] = str[i];
	newline[i] = '\0';
	tmp_str = malloc(strlen - i + 1);
	if (tmp_str == NULL)
	{
		free(newline);
		return (NULL);
	}
	j = -1;
	while (++j + i <= strlen)
		tmp_str[j] = str[j + i];
	free(lst_p->text);
	lst_p->text = tmp_str;
	lst_p->text_len = j - 1;
	return (newline);
}

char	*ft_strchar(char *str, char c)
{
	if (str == NULL)
		return (NULL);
	while (*str != '\0')
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}

t_gnl_list	*ft_newnode(int fd, t_gnl_list *previous)
{
	t_gnl_list	*newnode;

	newnode = malloc(sizeof(t_gnl_list));
	if (newnode == NULL)
		return (NULL);
	newnode->fd = fd;
	newnode->text = malloc(1);
	if (newnode->text == NULL)
	{
		free(newnode);
		return (NULL);
	}
	newnode->text[0] = '\0';
	newnode->text_len = 0;
	newnode->fin_flag = 0;
	newnode->previous = previous;
	newnode->next = NULL;
	return (newnode);
}

t_gnl_list	*ft_set_pointer(t_gnl_list **static_p, t_gnl_list **lst_p, int fd)
{
	if (*static_p == NULL)
		*static_p = ft_newnode(fd, NULL);
	if (*static_p == NULL)
		return (NULL);
	*lst_p = *static_p;
	while (1)
	{
		if ((*lst_p)->fd == fd)
			break ;
		if ((*lst_p)->next == NULL)
		{
			(*lst_p)->next = ft_newnode(fd, *lst_p);
			if ((*lst_p)->next == NULL)
				return (NULL);
		}
		(*lst_p) = (*lst_p)->next;
	}
	return (*lst_p);
}

char	*get_next_line(int fd)
{
	static t_gnl_list	*static_p;
	t_gnl_list			*lst_p;

	if (BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (NULL);
	lst_p = ft_set_pointer(&static_p, &lst_p, fd);
	if (lst_p == NULL)
		return (NULL);
	if (ft_strchar(lst_p->text, '\n'))
		return (ft_split_and_store_text(lst_p->text, lst_p->text_len, lst_p));
	if (lst_p->fin_flag == 1 && lst_p->text_len == 0)
		return (ft_delete_one_strage(&static_p, &lst_p));
	if (lst_p->fin_flag == 1)
		return (ft_push_end_line(&lst_p));
	return (ft_read_file_push_line(&lst_p, &static_p));
}
