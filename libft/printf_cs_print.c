/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cs_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:01:45 by faguirre          #+#    #+#             */
/*   Updated: 2024/10/09 12:02:24 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_utils.h"
#include "libft.h"
#include <stdarg.h>

void	print_cs(t_cs *cs, va_list args)
{
	if (cs->cs == '%')
		print_char('%', &(cs->n));
	else if (cs->cs == 'c')
		print_cs_c(cs, args);
	else if (cs->cs == 's')
		print_cs_s(cs, args);
	else if (cs->cs == 'i' || cs->cs == 'd')
		print_cs_d(cs, args);
	else if (cs->cs == 'u')
		print_cs_u(cs, args);
	else if (cs->cs == 'x')
		print_cs_x(cs, args, 0);
	else if (cs->cs == 'X')
		print_cs_x(cs, args, 1);
	else if (cs->cs == 'p')
		print_cs_p(cs, args);
	else
		cs->n = -1;
}
