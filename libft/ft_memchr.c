/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 22:40:05 by nfukuma           #+#    #+#             */
/*   Updated: 2022/07/13 01:42:48 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buf, int c, size_t n)
{
	const unsigned char	*uc_buf;
	unsigned char		uc_c;
	size_t				i;

	uc_buf = (const unsigned char *)buf;
	uc_c = (const unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (uc_buf[i] == uc_c)
			return ((void *)&uc_buf[i]);
		i++;
	}
	return (NULL);
}
