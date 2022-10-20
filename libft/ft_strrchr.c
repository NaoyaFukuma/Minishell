/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:41:21 by nfukuma           #+#    #+#             */
/*   Updated: 2022/07/08 23:36:21 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;
	char	*tmp_ptr;

	if (str == NULL)
		return (NULL);
	i = 0;
	tmp_ptr = NULL;
	while (1)
	{
		if (str[i] == (char)c)
			tmp_ptr = (char *)&str[i];
		if (str[i] == '\0')
			break ;
		i++;
	}
	return ((char *)tmp_ptr);
}
