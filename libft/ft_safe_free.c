/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 01:28:05 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/17 12:37:48 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_safe_free_single_ptr(void **target)
{
	free(*target);
	*target = NULL;
}

void	ft_safe_free_double_ptr(void ***target)
{
	size_t	i;

	if (!*target)
		return ;
	i = -1;
	while ((*target)[++i])
	{
		free((*target)[i]);
		(*target)[i] = NULL;
	}
	free(*target);
	*target = NULL;
}
