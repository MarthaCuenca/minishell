/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:42:39 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/25 20:53:55 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	varname_len_in_str(char *start)
{
	int		i;
	char	*end;
	char	*symbols[8];

	i = 0;
	end = NULL;
	symbols[0] = ft_strchr(start, ' ');
	symbols[1] = ft_strchr(start, '?');
	symbols[2] = ft_strchr(start, '\'');
	symbols[3] = ft_strchr(start, '\"');
	symbols[4] = ft_strchr(start, '$');
	symbols[5] = ft_strchr(start, '-');
	symbols[6] = ft_strchr(start, '\n');
	symbols[7] = ft_strchr(start, '\0');
	while (i < 8)
	{
		if (symbols[i] && (!end || symbols[i] < end))
			end = symbols[i];
		i++;
	}
	if ((end - start) == 0)
		return (1);
	return (end - start);
}

int	env_key_len(char *str, int c)
{
	int		i;
	char	*key;

	if (!str)
		return (0);
	i = 0;
	key = ft_strchr(str, c);
	if (!key)
		return (ft_strlen(str));
	while (str[i] && str[i] != *key)
		i++;
	return (i);
}

void	check_state(char *str, char *dollar, t_quote *quote_state)
{
	int		i;

	i = 0;
	while (str[i] && &str[i] != dollar)
	{
		if (str[i] == '\\')
			i++;
		if (str[i] == '\'')
		{
			if (*quote_state == NO_QUOTE)
				*quote_state = SIMPLE_QUOTE;
			else if (*quote_state == SIMPLE_QUOTE)
				*quote_state = NO_QUOTE;
		}
		else if (str[i] == '\"')
		{
			if (*quote_state == NO_QUOTE)
				*quote_state = DOUBLE_QUOTE;
			else if (*quote_state == DOUBLE_QUOTE)
				*quote_state = NO_QUOTE;
		}
		i++;
	}
}

t_bool	is_dollar_valid(char *str, char *dollar, t_bool is_heredoc)
{
	int		len;
	t_quote	quote_state;

	if (!dollar)
		return (FALSE);
	len = varname_len_in_str(dollar);
	quote_state = NO_QUOTE;
	check_state(str, dollar, &quote_state);
	if (quote_state == SIMPLE_QUOTE && is_heredoc == FALSE)
		return (FALSE);
	else if (!dollar[1])
		return (FALSE);
	else if (ft_prev_char(str, dollar) == '\\')
		return (FALSE);
	return (TRUE);
}

int	count_dollar(char *str, t_bool is_heredoc)
{
	int		count;
	char	*checkpoint;

	count = 0;
	checkpoint = str;
	while (checkpoint)
	{
		checkpoint = ft_strchr(checkpoint, '$');
		if (!checkpoint)
			break ;
		if (is_dollar_valid(str, checkpoint, is_heredoc))
			count++;
		if (is_special_dollar(checkpoint[1]) == TRUE)
			checkpoint++;
		checkpoint++;
	}
	return (count);
}
