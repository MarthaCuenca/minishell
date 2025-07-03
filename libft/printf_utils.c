/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:02:57 by faguirre          #+#    #+#             */
/*   Updated: 2024/10/09 12:57:39 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*free_strs(char *str1, char *str2, unsigned int num_free)
{
	if (num_free == 1 || num_free >= 3)
	{
		free(str1);
		str1 = NULL;
	}
	if (num_free == 2 || num_free >= 3)
	{
		free(str2);
		str2 = NULL;
	}
	return (NULL);
}

char	*char_in(const char *str, const char *set)
{
	return (ft_strchr(set, *str));
}

// Can control free inputs. Check if inputs are null, and if they are, free all
char	*strjoin_free(char *str1, char *str2, unsigned int num_free)
{
	size_t	n1;
	size_t	n2;
	char	*result;

	if (!str1 || !str2)
		return (free_strs(str1, str2, 3));
	n1 = ft_strlen(str1);
	n2 = ft_strlen(str2);
	result = (char *)malloc(n1 + n2 + 1);
	if (!result)
		return (free_strs(str1, str2, 3));
	ft_strlcpy(result, str1, n1 + 1);
	ft_strlcpy(&result[n1], str2, n2 + 1);
	free_strs(str1, str2, num_free);
	return (result);
}

void	print_char(char c, int *result)
{
	if (!ft_putchar_fd(c, 1))
		*result = -1;
	else
		*result += 1;
}

void	print_str(char *str, int *result)
{
	if (!ft_putstr_fd(str, 1))
		*result = -1;
	else
		*result += ft_strlen(str);
}
