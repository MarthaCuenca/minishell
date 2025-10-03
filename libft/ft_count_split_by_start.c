/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_by_start.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:13:17 by faguirre          #+#    #+#             */
/*   Updated: 2025/10/02 16:30:09 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

int	*ft_count_split_by_start(char **split, char *starts)
{
	int	*result;
	int	n;
	int	i;

	n = ft_strlen(starts);
	result = ft_calloc(n + 1, sizeof (int));
	if (!result)
		return (NULL);
	while (*split)
	{
		i = -1;
		while (starts[++i])
		{
			if (split[0][0] == starts[i])
			{
				result[i]++;
				break ;
			}
		}
		if (i == n)
			result[i]++;
		split++;
	}
	return (result);
}
