/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:51:14 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/27 13:33:17 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_samealloc_diffpos(char *str, char *ptr)
{
	int		len;
	char	*str_len;

	len = ft_strlen(str);
	str_len = str + len;
	if (ptr > str && ptr < str_len)
		return (1);
	return (0);
}

char	ft_prev_char(char *str, char *subptr)
{
	int	i;

	if (str == subptr)
		return ('\0');
	if (!ft_is_samealloc_diffpos(str, subptr))
		return ('\0');
	i = 0;
	while (str[i] && &str[i + 1] != subptr)
		i++;
	return (str[i]);
}

t_bool	is_c_symbol(char c, char *symbols)
{
	int	i;

	if (!symbols)
		return (FALSE);
	i = 0;
	while (symbols[i] && c != symbols[i])
		i++;
	if (c == symbols[i])
		return (TRUE);
	return (FALSE);
}

t_bool	is_x_symbol(int x, int *symbols, int len)
{
	int	i;

	if (!symbols)
		return (FALSE);
	i = 0;
	while (i < len && x != symbols[i])
		i++;
	if (x == symbols[i])
		return (TRUE);
	return (FALSE);
}
