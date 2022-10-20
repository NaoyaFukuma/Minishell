/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 22:45:42 by nfukuma           #+#    #+#             */
/*   Updated: 2022/07/16 21:26:46 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*map_s;
	size_t	i;

	if (s == NULL || f == NULL)
		return (NULL);
	map_s = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (map_s == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		map_s[i] = f(i, s[i]);
		i++;
	}
	return (map_s);
}
