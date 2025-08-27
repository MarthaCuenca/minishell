/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 09:53:11 by faguirre          #+#    #+#             */
/*   Updated: 2025/08/25 19:40:47 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	s--;
	while (*(++s))
	{
		if (*s == c)
			return ((char *)s);
	}
	if (*s == c)
		return ((char *)s);
	return ((void *)0);
}

int	count_char_repeat(const char *s, int c)
{
	int		i;
	char	*new_s;

	if (!s || !c)
		return (0);
	i = 0;
	new_s = (char *)s;
	while (new_s)
	{
		new_s = ft_strchr(new_s, c);
		if (!new_s)
			break ;
		new_s++;
		i++;
	}
	return (i);
}
