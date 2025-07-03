/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:35:05 by faguirre          #+#    #+#             */
/*   Updated: 2024/09/20 17:36:01 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!(*little))
		return ((char *)big);
	j = 0;
	while ((big[j]) && (j < len))
	{
		i = 0;
		while (little[i] && big[i + j] && (big[i + j] == little[i]) \
				&& (i + j < len))
		{
			i++;
		}
		if (!little[i])
			return ((char *)(&big[j]));
		j++;
	}
	return ((void *)0);
}
