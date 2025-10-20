/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:15:17 by faguirre          #+#    #+#             */
/*   Updated: 2025/10/17 18:40:42 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (2048);
	}
	return (0);
}

void	ft_isspace(const char *str, int *i)
{
	while (str[*i] && (str[*i] == 32 || (str[*i] >= 9 && str[*i] <= 13)))
		(*i)++;
}

int	ft_str_isdigit(const char *str)
{
	int	i;

	i = 0;
	ft_isspace(str, &i);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (!(ft_isdigit(str[i])))
		{
			ft_isspace(str, &i);
			if (str[i])
				return (0);
			else
				return (1);
		}
		i++;
	}
	return (1);
}

