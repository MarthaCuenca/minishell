/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cs_print_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:02:17 by faguirre          #+#    #+#             */
/*   Updated: 2024/10/09 11:02:20 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf_utils.h"
#include <stdlib.h>

// If printing an %iducs..., manage the 0-. interaction outside
void	print_width(char *str, t_cs *cs)
{
	int		n;
	int		i;
	char	spacing_char;

	spacing_char = ' ';
	if (cs->is_zero)
		spacing_char = '0';
	n = (int)ft_strlen(str);
	if (cs->width > n)
	{
		if (cs->is_neg)
			print_str(str, &(cs->n));
		i = -1;
		while (++i < cs->width - n)
			print_char(spacing_char, &(cs->n));
		if (!cs->is_neg)
			print_str(str, &(cs->n));
	}
	else
		print_str(str, &(cs->n));
}

// return 0 if fail
int	check_str_malloc(char *str, int *result)
{
	if (!str)
	{
		*result = -1;
		return (0);
	}
	return (1);
}

char	*strdup_char(char c)
{
	char	*result;

	result = (char *)malloc(2);
	if (!result)
		return (NULL);
	result[0] = c;
	result[1] = '\0';
	return (result);
}

int	process_null_ptr(t_cs *cs)
{
	char	*str;

	if (cs->cs == 'p')
		str = ft_strdup("(nil)");
	else if (cs->cs == 's')
		str = ft_strdup("(null)");
	else
		return (0);
	if (!check_str_malloc(str, &(cs->n)))
		return (0);
	print_width(str, cs);
	free(str);
	return (1);
}
