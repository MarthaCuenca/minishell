/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:35:05 by faguirre          #+#    #+#             */
/*   Updated: 2025/08/11 14:05:51 by mcuenca-         ###   ########.fr       */
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

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	i;
	int	j;

	if (!haystack || !needle)
		return (NULL);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while(haystack[i + j] == needle[j])
			j++;
		if (!needle[j])
			return ((char *)(&haystack[i]));
		i++;
	}
	return (NULL);
}

char	*ft_strrstr(const char *haystack, const char *needle)
{
	int	i;
	int	j;

	if (!haystack || !needle)
		return (NULL);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while(haystack[i + j] && needle[i] && haystack[i + j] == needle[j])
			j++;
		if (!needle[j])
			return ((char *)(&haystack[i + j]));
		i++;
	}
	return (NULL);
}


int	ft_strrstr_count(const char *haystack, const char *needle)
{
	int		count;
	char	*tmp;

	if (!haystack || !needle)
		return (0);
	count = 0;
	tmp = (char *)haystack;
	while (tmp)
	{
		count++;
		tmp++;
		tmp = ft_strrstr(tmp, needle);
	}
	return (count);
}
