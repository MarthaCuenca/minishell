/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:22:07 by faguirre          #+#    #+#             */
/*   Updated: 2024/09/18 04:08:00 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*s1_c;
	const char	*s2_c;
	size_t		i;

	s1_c = s1;
	s2_c = s2;
	i = 0;
	while (s1_c[i] && s2_c[i] && (i < n))
	{
		if (s1_c[i] != s2_c[i])
			return (s1_c[i] - s2_c[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (s1_c[i] - s2_c[i]);
}
