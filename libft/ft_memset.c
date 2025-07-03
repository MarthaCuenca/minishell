/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:44:09 by faguirre          #+#    #+#             */
/*   Updated: 2024/09/18 04:10:20 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	c_u;
	unsigned char	*s_c;
	size_t			i;

	s_c = (unsigned char *)s;
	c_u = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		s_c[i] = c_u;
		i++;
	}
	return (s);
}
