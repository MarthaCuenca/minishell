/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:13:53 by faguirre          #+#    #+#             */
/*   Updated: 2025/10/02 19:28:13 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_join_path(char *str1, char *str2)
{
	char	*result;
	char	*tmp_join;

	if (str1[ft_strlen(str1) - 1] == '/')
	{
		if (str2[0] == '/')
			result = ft_strjoin(str1, str2 + 1);
		else
			result = ft_strjoin(str1, str2);
	}
	else
	{
		if (str2[0] == '/')
			return (ft_strjoin(str1, str2));
		tmp_join = ft_strjoin(str1, "/");
		if (!tmp_join)
			return (NULL);
		result = ft_strjoin(tmp_join, str2);
		free(tmp_join);
	}
	return (result);
}
