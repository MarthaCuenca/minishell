/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:14:20 by faguirre          #+#    #+#             */
/*   Updated: 2024/09/23 15:44:43 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	n;

	if (!s1 || !set)
	{
		return ((void *)0);
	}
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	n = ft_strlen(s1);
	while (n > 0 && ft_strchr(set, s1[n - 1]))
	{
		n--;
	}
	result = (char *)malloc((ft_strlen(s1) + 1) * sizeof (char));
	if (!result)
		return (result);
	ft_strlcpy(result, s1, n + 1);
	return (result);
}
