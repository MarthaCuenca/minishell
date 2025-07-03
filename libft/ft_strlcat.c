/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 09:21:35 by faguirre          #+#    #+#             */
/*   Updated: 2024/09/20 10:04:06 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	n_dst;
	size_t	n_src;

	n_src = ft_strlen(src);
	n_dst = ft_strlen(dst);
	if (size <= n_dst)
	{
		return (size + n_src);
	}
	ft_strlcpy(&dst[n_dst], src, size - n_dst);
	return (n_dst + n_src);
}
