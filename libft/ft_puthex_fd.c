/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:10:44 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/02 00:11:20 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthex_fd(unsigned int n, bool format, int fd)
{
	if (0 == n)
		write(fd, "0", 1);
	else
	{
		if (n / 16 != 0)
		{
			ft_puthex_fd(n / 16, format, fd);
		}
		if (format == true)
			write(fd, &"0123456789abcdef"[n % 16], 1);
		else
			write(fd, &"0123456789ABCDEF"[n % 16], 1);
	}
}

void	ft_puthex_ul_fd(unsigned long n, bool format, int fd)
{
	if (0 == n)
		write(fd, "0", 1);
	else
	{
		if (n / 16 != 0)
		{
			ft_puthex_ul_fd(n / 16, format, fd);
		}
		if (format == true)
			write(fd, &"0123456789abcdef"[n % 16], 1);
		else
			write(fd, &"0123456789ABCDEF"[n % 16], 1);
	}
}
