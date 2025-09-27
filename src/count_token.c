/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:13:08 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/09/13 13:40:58 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_count_tk(size_t count_tk, int quote_state)
{
	if (quote_state != NO_QUOTE)
		return (0);
	if (count_tk == 0)
		return (1);
	return (count_tk);
}

static int	no_quote(char *cmmd, int *quote_state, int *count_tk, int *bool_tk)
{
	int	i;

	i = 0;
	if (cmmd[i] == '\'')
		*quote_state = SIMPLE_QUOTE;
	else if (cmmd[i] == '\"')
		*quote_state = DOUBLE_QUOTE;
	else if (cmmd[i] == ' ')
		*bool_tk = FALSE;
	else
	{
		if (*bool_tk == FALSE)
		{
			(*count_tk)++;
			*bool_tk = TRUE;
		}
	}
	i++;
	return (i);
}

static int	sim_quote(char *cmmd, int *quote_state, int *count_tk, int *bool_tk)
{
	int	i;

	i = 0;
	while (cmmd[i] && cmmd[i] != 39)
		i++;
	if (cmmd[i] == 39)
	{
		*quote_state = NO_QUOTE;
		(*count_tk)++;
		i++;
		*bool_tk = FALSE;
	}
	return (i);
}

static int	dou_quote(char *cmmd, int *quote_state, int *count_tk, int *bool_tk)
{
	int	i;

	i = 0;
	while (cmmd[i] && cmmd[i] != 34)
		i++;
	if (cmmd[i] == 34)
	{
		*quote_state = NO_QUOTE;
		(*count_tk)++;
		i++;
		*bool_tk = FALSE;
	}
	return (i);
}

int	count_token(char *cmmd)
{
	int	i;
	int	quote_state;
	int	count_tk;
	int	bool_tk;

	if (!cmmd)
		return (0);
	i = 0;
	quote_state = NO_QUOTE;
	count_tk = 0;
	bool_tk = FALSE;
	while (6 < cmmd[i] && 14 > cmmd[i] && cmmd[i] != 32)
		i++;
	while (cmmd[i])
	{
		if (quote_state == SIMPLE_QUOTE)
			i += sim_quote(&cmmd[i], &quote_state, &count_tk, &bool_tk);
		else if (quote_state == DOUBLE_QUOTE)
			i += dou_quote(&cmmd[i], &quote_state, &count_tk, &bool_tk);
		else
			i += no_quote(&cmmd[i], &quote_state, &count_tk, &bool_tk);
	}
	return (check_count_tk(count_tk, quote_state));
}
