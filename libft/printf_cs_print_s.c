/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cs_print_s.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:02:05 by faguirre          #+#    #+#             */
/*   Updated: 2024/10/09 11:02:07 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_utils.h"
#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>

void	print_cs_s(t_cs *cs, va_list args)
{
	char	*s;

	s = va_arg(args, char *);
	if (!s)
	{
		print_str("(null)", &(cs->n));
		return ;
	}
	cs->is_zero = 0;
	if (cs->precision != -1 && cs->precision < (int)ft_strlen(s))
	{
		s = ft_substr(s, 0, cs->precision);
		if (!s)
		{
			cs->n = -1;
			return ;
		}
		print_width(s, cs);
		free(s);
	}
	else
		print_width(s, cs);
}

void	print_cs_c(t_cs *cs, va_list args)
{
	unsigned char	c;
	int				i;

	c = va_arg(args, int);
	if (cs->width > 1)
	{
		if (cs->is_neg)
			print_char(c, &(cs->n));
		i = -1;
		while (++i < cs->width - 1)
			print_char(' ', &(cs->n));
		if (!cs->is_neg)
			print_char(c, &(cs->n));
	}
	else
		print_char(c, &(cs->n));
}
