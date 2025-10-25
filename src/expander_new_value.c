/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_new_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:50:12 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/25 20:51:11 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	fill_new_str(char *dest, char **values, char *str, t_bool is_heredoc)
{
	int	i;
	int	j;
	int	k;
	int	value_len;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '$' && is_dollar_valid(str, &str[i], is_heredoc))
		{
			i += varname_len_in_str(&str[i] + 1) + 1;
			value_len = ft_strlen(values[j]);
			ft_memcpy(&dest[k], values[j], value_len);
			k += value_len;
			j++;
		}
		else
			dest[k++] = str[i++];
	}
	dest[k] = '\0';
}

char	*exchange_exp_var(char **values, char *str, t_bool is_heredoc)
{
	int		j;
	int		len;
	char	*new_str;

	j = 0;
	len = ft_strlen(str);
	while (values[j])
		len += ft_strlen(values[j++]);
	new_str = (char *)ft_calloc((len + 1), sizeof(char));
	if (!new_str)
		return (malloc_err(), NULL);
	fill_new_str(new_str, values, str, is_heredoc);
	return (new_str);
}
