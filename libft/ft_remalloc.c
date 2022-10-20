/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 23:23:18 by nfukuma           #+#    #+#             */
/*   Updated: 2022/09/07 09:48:20 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_remalloc(void *old, size_t new_size, size_t old_size)
{
	void	*new;

	if (!old)
		return (malloc(new_size));
	else if (!new_size)
	{
		free(old);
		return (NULL);
	}
	new = malloc(new_size);
	if (!new)
		return (NULL);
	ft_memcpy(new, old, old_size);
	free(old);
	return (new);
}
