/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:01:28 by faguirre          #+#    #+#             */
/*   Updated: 2024/10/09 11:01:31 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_utils.h"
#include "libft.h"

static t_cs	init_cs(void)
{
	t_cs	cs;

	cs.cs = 0;
	cs.is_hash = 0;
	cs.is_zero = 0;
	cs.is_neg = 0;
	cs.is_space = 0;
	cs.is_pos = 0;
	cs.width = 0;
	cs.precision = -1;
	cs.load_ok = 1;
	cs.n = 0;
	return (cs);
}

static void	load_precision(t_cs *cs, const char **str)
{
	if (!ft_isdigit((*str)[1]))
	{
		cs->precision = 0;
		return ;
	}
	(*str)++;
	cs->precision = ft_atoi(*str);
	while (ft_isdigit((*str)[1]))
		(*str)++;
}

static void	load_width(t_cs *cs, const char **str)
{
	cs->width = ft_atoi(*str);
	while (ft_isdigit((*str)[1]))
		(*str)++;
}

static void	load_flag(t_cs *cs, const char **c)
{
	if (char_in(*c, "#0- +") && !(cs->width || cs->precision > -1))
	{
		if (**c == '#')
			cs->is_hash = 1;
		if (**c == '0')
			cs->is_zero = 1;
		if (**c == '-')
			cs->is_neg = 1;
		if (**c == ' ')
			cs->is_space = 1;
		if (**c == '+')
			cs->is_pos = 1;
	}
	else if (ft_isdigit(**c) && !(cs->width || cs->precision > -1))
		load_width(cs, c);
	else if ((**c == '.') && (cs->precision == -1))
		load_precision(cs, c);
	else
		cs->load_ok = 0;
}

/* Load flags, advance pointer until conversion specifier or \0
   if load fails, only advance 1 position */
t_cs	load_cs(const char **str)
{
	t_cs		cs;
	const char	*str_start;

	str_start = *str;
	(*str)++;
	cs = init_cs();
	while (**str && !char_in(*str, "cspdiuxX%") && cs.load_ok)
	{
		load_flag(&cs, str);
		(*str)++;
	}
	if (!(cs.load_ok) || !(**str))
	{
		*str = str_start;
		cs.load_ok = 0;
	}
	if (char_in(*str, "cspdiuxX%"))
		cs.cs = **str;
	return (cs);
}
