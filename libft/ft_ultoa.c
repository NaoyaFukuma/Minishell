/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 22:10:12 by nfukuma           #+#    #+#             */
/*   Updated: 2022/07/16 22:14:27 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_recursive_create_str(char *str, unsigned long n)
{
	if (n > 9)
		str = ft_recursive_create_str(str, (n / 10));
	*str++ = (n % 10 + '0');
	return (str);
}

static size_t	ft_get_digits(unsigned long n)
{
	size_t	digits;

	digits = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_ultoa(unsigned long n)
{
	char		*str;
	size_t		digits;

	digits = ft_get_digits(n);
	str = ft_calloc((digits + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	str = ft_recursive_create_str(str, n);
	return (str - digits);
}
