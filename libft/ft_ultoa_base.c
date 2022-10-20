/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 23:48:06 by nfukuma           #+#    #+#             */
/*   Updated: 2022/07/19 17:05:46 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_recursive_create_str(char *str, unsigned long n, int base,
		char *base_set)
{
	if (n >= (unsigned long)base)
		str = ft_recursive_create_str(str, (n / base), base, base_set);
	*str++ = base_set[n % base];
	return (str);
}

static size_t	ft_get_digits(unsigned long n, int base)
{
	size_t	digits;

	digits = 1;
	while (n / base != 0)
	{
		n /= base;
		digits++;
	}
	return (digits);
}

char	*ft_ultoa_base(unsigned long n, int base, char *base_set)
{
	char	*str;
	size_t	digits;

	digits = ft_get_digits(n, base);
	str = ft_calloc((digits + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	str = ft_recursive_create_str(str, n, base, base_set);
	return (str - digits);
}
