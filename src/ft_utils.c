/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:51:14 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/25 18:53:29 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_x_symbol(int x, int *symbols, int len)
{
	int	i;

	if (!symbols)
		return (FALSE);
	i = 0;
	while (i < len && x != symbols[i])
		i++;
	if (x == symbols[i])
		return (TRUE);
	return (FALSE);
}
