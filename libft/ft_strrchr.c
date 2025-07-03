/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:12:57 by faguirre          #+#    #+#             */
/*   Updated: 2024/09/14 10:29:03 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	const char	*start;

	start = s;
	while (*s)
	{
		s++;
	}
	s++;
	while ((--s) >= start)
	{
		if (*s == c)
			return ((char *)s);
	}
	return ((void *)0);
}
