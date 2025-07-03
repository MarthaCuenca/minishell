/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:34:38 by faguirre          #+#    #+#             */
/*   Updated: 2024/09/23 15:43:01 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	size_t	n;
	size_t	i;
	char	*result;

	n = ft_strlen(s);
	result = (char *)malloc((n + 1) * sizeof (char));
	if (!result)
		return ((void *)0);
	i = 0;
	while (i < n)
	{
		result[i] = s[i];
		i++;
	}
	result[n] = '\0';
	return (result);
}
