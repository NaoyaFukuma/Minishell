/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:45:13 by nfukuma           #+#    #+#             */
/*   Updated: 2022/07/11 15:37:44 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_all(char **split_strs, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		free(split_strs[i]);
		i++;
	}
	free(split_strs);
	return (NULL);
}

static size_t	splitstr_len(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] != (char)c)
		i++;
	return (i);
}

static const char	*ignore_c(const char *str, int c)
{
	while (*str == c && *str != '\0')
		str++;
	return (str);
}

static size_t	count_str(const char *str, char c)
{
	size_t	count;

	count = 0;
	while (1)
	{
		if (*str == c)
			str = ignore_c(str, c);
		if (*str != '\0')
		{
			str += splitstr_len(str, c);
			count++;
		}
		if (*str == '\0')
			break ;
	}
	return (count);
}

char	**ft_split(const char *str, char c)
{
	char	**split_strs;
	size_t	str_count;
	size_t	str_len;
	size_t	i;

	if (str == NULL)
		return (NULL);
	str_count = count_str(str, c);
	split_strs = malloc(sizeof(char *) * (str_count + 1));
	if (split_strs == NULL)
		return (NULL);
	i = 0;
	while (i < str_count)
	{
		str = ignore_c(str, c);
		str_len = splitstr_len(str, c);
		split_strs[i] = malloc(sizeof(char) * (str_len + 1));
		if (split_strs[i] == NULL)
			return (free_all(split_strs, i));
		ft_strlcpy(split_strs[i], str, str_len + 1);
		str += str_len;
		i++;
	}
	split_strs[str_count] = NULL;
	return (split_strs);
}
