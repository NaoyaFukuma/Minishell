/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:57:15 by nfukuma           #+#    #+#             */
/*   Updated: 2022/07/16 21:26:46 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	size_t	str_len;
	char	*substr;

	if (str == NULL)
		return (NULL);
	str_len = ft_strlen(str);
	if (len == 0 || str_len <= start)
		return (ft_strdup(""));
	if (len >= str_len - start)
		len = str_len - start;
	substr = malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (NULL);
	ft_strlcpy(substr, &str[start], len + 1);
	return (substr);
}
