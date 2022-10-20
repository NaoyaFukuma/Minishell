/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:38:56 by nfukuma           #+#    #+#             */
/*   Updated: 2022/07/16 21:26:46 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

static bool	isset(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (true);
		set++;
	}
	return (false);
}

static size_t	trimstrlen(const char *str, const char *set)
{
	size_t	endpoint;

	endpoint = ft_strlen(str);
	while (isset(str[endpoint - 1], set) == true)
		endpoint--;
	return ((size_t)(&str[endpoint] - str));
}

char	*ft_strtrim(const char *str, const char *set)
{
	char	*res_str;
	size_t	res_str_ren;

	if (str == NULL || set == NULL)
		return (NULL);
	while (isset(*str, set) == true)
		str++;
	res_str_ren = trimstrlen(str, set);
	res_str = malloc(sizeof(char) * (res_str_ren + 1));
	ft_strlcpy(res_str, str, res_str_ren + 1);
	return (res_str);
}
