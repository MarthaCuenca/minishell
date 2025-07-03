/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:23:43 by faguirre          #+#    #+#             */
/*   Updated: 2024/09/25 20:47:36 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count_splits(char const *s, char c)
{
	int	i;
	int	result;

	result = 0;
	i = 0;
	if (!s[i])
		return (result);
	if (s[i] != c)
		result++;
	while (s[i])
	{
		if (s[i + 1] && (s[i] == c) && (s[i + 1] != c))
		{
			result++;
		}
		i++;
	}
	return (result);
}

static char	**create_node(char **tab, char const *s, size_t i[3])
{
	size_t	i_free;

	tab[i[2]] = ft_substr(s, i[0], i[1] - i[0] + 1);
	if (!tab[i[2]])
	{
		i_free = 0;
		while (i_free < i[2])
		{
			free(tab[i_free]);
			i_free++;
		}
		free(tab);
		return (NULL);
	}
	return (tab);
}

static char	**create_splits(char **tab, char const *s, char c)
{
	size_t	i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!s[i[1]])
	{
		tab[i[2]] = NULL;
		return (tab);
	}
	while (s[i[1]])
	{
		if (s[i[1]] == c && s[i[1] + 1] != c)
			i[0] = i[1] + 1;
		if ((s[i[1]] != c) && (s[i[1] + 1] == c || !s[i[1] + 1]))
		{
			tab = create_node(tab, s, i);
			if (!tab)
				return (NULL);
			i[2]++;
		}
		i[1]++;
	}
	tab[i[2]] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = (char **)malloc((count_splits(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result = create_splits(result, s, c);
	if (!result)
	{
		return (NULL);
	}
	return (result);
}
