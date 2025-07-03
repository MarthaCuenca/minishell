/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cs_print_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:01:57 by faguirre          #+#    #+#             */
/*   Updated: 2024/10/09 11:11:33 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_utils.h"
#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>

void	print_cs_u(t_cs *cs, va_list args)
{
	int		n;
	char	*str;

	str = ft_itoa(va_arg(args, unsigned int));
	if (!check_str_malloc(str, &(cs->n)))
		return ;
	n = (int)ft_strlen(str);
	while (cs->precision > n++)
		str = strjoin_free("0", str, 2);
	if (!check_str_malloc(str, &(cs->n)))
		return ;
	if (cs->is_neg || cs->precision != -1)
		cs->is_zero = 0;
	print_width(str, cs);
	free(str);
}

void	print_cs_d(t_cs *cs, va_list args)
{
	int		num;
	int		n;
	char	*str;

	num = va_arg(args, int);
	str = ft_itoa(num);
	if (!check_str_malloc(str, &(cs->n)))
		return ;
	n = (int)ft_strlen(str);
	while (cs->precision > n++)
		str = strjoin_free("0", str, 2);
	if ((cs->is_space || cs->is_pos) && num >= 0)
	{
		if (cs->is_space && !cs->is_pos)
			str = strjoin_free(" ", str, 2);
		else
			str = strjoin_free("+", str, 2);
	}
	if (!check_str_malloc(str, &(cs->n)))
		return ;
	if (cs->is_neg || cs->precision != -1)
		cs->is_zero = 0;
	print_width(str, cs);
	free(str);
}
