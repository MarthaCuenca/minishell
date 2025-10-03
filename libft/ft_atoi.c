/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:33:22 by faguirre          #+#    #+#             */
/*   Updated: 2025/09/25 14:39:29 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_overflow(char *str)
{
	int		sign;
	int		len;
	char	*start;

	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	start = str;
	while (ft_isdigit(*str))
		str++;
	len = str - start;
	if (len > 10)
		return (1);
	if (len == 10
		&& ((sign == 1 && ft_strcmp(start, MAX_INT_CHAR) > 0)
			|| (sign == -1 && ft_strcmp(start, MIN_INT_CHAR) > 0)))
		return (1);
	return (0);
}

static const char	*calculate_sign(const char *str, long *sign)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			(*sign) *= -1;
		str++;
	}
	return (str);
}

int	ft_atoi(const char *nptr)
{
	long	result;
	long	sign;

	sign = 1;
	nptr = calculate_sign(nptr, &sign);
	result = 0;
	while (*nptr && (*nptr >= '0') && (*nptr <= '9'))
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	result = sign * result;
	return ((int)result);
}
