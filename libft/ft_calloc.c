/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:08:23 by faguirre          #+#    #+#             */
/*   Updated: 2024/09/18 04:09:23 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <limits.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*result;

	if (size != 0)
	{
		if (nmemb > ULLONG_MAX / size)
			return (NULL);
	}
	result = malloc(nmemb * size);
	if (!result)
		return (result);
	ft_bzero(result, nmemb * size);
	return (result);
}
