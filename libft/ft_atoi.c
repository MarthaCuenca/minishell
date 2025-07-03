/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:33:22 by faguirre          #+#    #+#             */
/*   Updated: 2024/09/16 08:46:24 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
