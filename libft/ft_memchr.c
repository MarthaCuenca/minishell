/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:52:10 by faguirre          #+#    #+#             */
/*   Updated: 2024/09/18 04:13:26 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	c_u;
	size_t			i;

	str = (unsigned char *)s;
	c_u = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == c_u)
		{
			return ((void *)(&str[i]));
		}
		i++;
	}
	return ((void *)0);
}
