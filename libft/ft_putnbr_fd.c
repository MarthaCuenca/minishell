/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 02:14:23 by faguirre          #+#    #+#             */
/*   Updated: 2024/09/18 02:45:33 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	putnbr_recursive(long n, int fd)
{
	if (n < 0)
	{
		if (!ft_putchar_fd('-', fd))
			return (0);
		n = -n;
	}
	if (n > 9)
	{
		if (!putnbr_recursive(n / 10, fd))
			return (0);
	}
	if (!ft_putchar_fd((n % 10) + '0', fd))
		return (0);
	return (1);
}

int	ft_putnbr_fd(int n, int fd)
{
	if (!putnbr_recursive(n, fd))
		return (0);
	return (1);
}
