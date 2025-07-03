/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cs_print_x.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:02:29 by faguirre          #+#    #+#             */
/*   Updated: 2024/10/10 14:34:57 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_utils.h"
#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>

static char	*itohex(unsigned long num, char is_upper)
{
	const char	hex_l[16] = "0123456789abcdef";
	const char	hex_u[16] = "0123456789ABCDEF";
	char		*hex;
	char		*result;

	if (is_upper)
		hex = (char *)hex_u;
	else
		hex = (char *)hex_l;
	result = ft_strdup("");
	if (num == 0)
	{
		free(result);
		return (ft_strdup("0"));
	}
	while (num > 0)
	{
		result = strjoin_free(strdup_char(hex[num % 16]), result, 3);
		num /= 16;
	}
	return (result);
}

static void	process_x(unsigned int num, char **str, t_cs *cs, char is_upper)
{
	int	n;

	n = (int)ft_strlen(*str);
	if (cs->is_neg || cs->precision != -1)
		cs->is_zero = 0;
	if (cs->is_hash && cs->is_zero && num != 0)
	{
		cs->precision = cs->width - 2;
		cs->width = 0;
	}
	while (cs->precision > n++)
		*str = strjoin_free("0", *str, 2);
	if (cs->is_hash && num != 0)
	{
		if (is_upper)
			*str = strjoin_free("0X", *str, 2);
		else
			*str = strjoin_free("0x", *str, 2);
	}
	if ((int)ft_strlen(*str) >= cs->width)
		cs->width = 0;
}

void	print_cs_x(t_cs *cs, va_list args, char is_upper)
{
	unsigned int	num;
	char			*str;

	num = va_arg(args, unsigned int);
	str = itohex(num, is_upper);
	if (!check_str_malloc(str, &(cs->n)))
		return ;
	process_x(num, &str, cs, is_upper);
	if (!check_str_malloc(str, &(cs->n)))
		return ;
	print_width(str, cs);
	free(str);
}

void	print_cs_p(t_cs *cs, va_list args)
{
	void	*ptr;
	char	*str;

	ptr = va_arg(args, void *);
	if (!ptr)
	{
		process_null_ptr(cs);
		return ;
	}
	str = itohex((unsigned long)ptr, 0);
	if (!check_str_malloc(str, &(cs->n)))
		return ;
	cs->is_hash = 1;
	process_x(1, &str, cs, 0);
	if ((cs->is_space || cs->is_pos))
	{
		if (cs->is_space && !cs->is_pos)
			str = strjoin_free(" ", str, 2);
		else
			str = strjoin_free("+", str, 2);
	}
	if (!check_str_malloc(str, &(cs->n)))
		return ;
	print_width(str, cs);
	free(str);
}
