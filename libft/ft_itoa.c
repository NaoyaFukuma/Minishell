/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 22:38:26 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/18 12:53:17 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_recursive_create_str(char *str, long long long_long_n)
{
	if (long_long_n > 9)
		str = ft_recursive_create_str(str, (long_long_n / 10));
	*str++ = (long_long_n % 10 + '0');
	return (str);
}

static size_t	ft_get_digits(long long long_long_n)
{
	size_t	digits;

	digits = 1;
	if (long_long_n < 0)
		digits++;
	while (long_long_n / 10)
	{
		long_long_n /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char		*str;
	long long	long_long_n;
	size_t		digits;

	long_long_n = n;
	digits = ft_get_digits(long_long_n);
	str = malloc(sizeof(char) * (digits + 1));
	if (str == NULL)
		return (NULL);
	str[digits] = '\0';
	if (long_long_n < 0)
	{
		*str = '-';
		long_long_n *= -1;
	}
	str = ft_recursive_create_str(str, long_long_n);
	return (str - digits);
}
