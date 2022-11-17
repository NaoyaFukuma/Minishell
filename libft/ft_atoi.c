/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 22:10:28 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/17 12:47:43 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <limits.h>

static const char	*ft_sign_flag(const char *str, int *sign_flag)
{
	*sign_flag = 1;
	if (*str == '-')
	{
		str++;
		*sign_flag = -1;
	}
	else if (*str == '+')
		str++;
	return (str);
}

int	ft_atoi(const char *str)
{
	long	res;
	int		sign_flag;

	while (ft_isspace(*str))
		str++;
	str = ft_sign_flag(str, &sign_flag);
	res = 0;
	while (ft_isdigit(*str))
	{
		if (sign_flag == 1 && (res > ((LONG_MAX - (*str - '0')) * sign_flag)
				/ 10))
		{
			errno = ERANGE;
			return ((int)LONG_MAX);
		}
		else if (sign_flag == -1 && (res < ((LONG_MIN - (*str - '0'))
					* sign_flag) / 10))
		{
			errno = ERANGE;
			return ((int)LONG_MIN);
		}
		res = (10 * res) + ((*str - '0') * sign_flag);
		str++;
	}
	return ((int)res);
}

bool	ft_atoi_limit(const char *str, int *return_value)
{
	int				i;
	int				sign;
	unsigned long	div;
	unsigned long	res;

	i = 0;
	res = 0;
	div = INT_MAX / 10;
	sign = 1;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ('0' <= str[i] && str[i] <= '9'))
	{
		if (((div < res || (div == res && str[i] > '7')) && sign == 1) \
			|| ((div < res || (div == res && str[i] > '8')) && sign == -1))
			return (false);
		res *= 10;
		res += str[i++] - '0';
	}
	*return_value = (int)res * sign;
	return (true);
}
