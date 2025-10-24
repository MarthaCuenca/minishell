/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_static_itoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:22:52 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/24 19:14:10 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_count_digits(long int n)
{
	int	count;

	if (n > 2147483647 || n < -2147483647)
		return (0);
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	count = 0;
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_static_itoa(char *dest, int size, long int n)
{
	int	digits;

	if (!dest || size <= 0 || size > 12 || n > 2147483647 || n < -2147483647)
		return (NULL);
	digits = ft_count_digits(n);
	if (n < 0)
	{
		n *= -1;
		dest[0] = '-';
		digits++;
	}
	if (digits >= size)
	{
		dest[0] = '\0';
		return (NULL);
	}
	dest[digits] = '\0';
	while (digits-- > 0)
	{
		dest[digits] = (n % 10) + '0';
		n = n / 10;
	}
	return (dest);
}
