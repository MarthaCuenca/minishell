/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:45:07 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/09/19 14:35:45 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_2p(char **array)
{
	size_t	i;

	if (!array || !*array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}
