/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_token_quote_mng.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:26:48 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/27 18:34:21 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int	double_quo(char *cmmd, int *qs, int *i)
{
	int	tmp;

	tmp = *i + 1;
	*qs = DOUBLE_QUOTE;
	while (cmmd[tmp] && cmmd[tmp] != '\"')
	{
		if (cmmd[tmp] == '`')
			return (-1);
		if (cmmd[tmp] == '\\'
			&& (cmmd[tmp + 1] == '\"' || cmmd[tmp + 1] == '`'))
			tmp++;
		tmp++;
	}
	if (cmmd[tmp] == '\"')
	{
		*qs = NO_QUOTE;
		*i = tmp;
		return (tmp);
	}
	return (-1);
}

static int	simple_quo(char *cmmd, int *qs, int *i)
{
	int	tmp;

	tmp = *i + 1;
	*qs = SIMPLE_QUOTE;
	while (cmmd[tmp] && cmmd[tmp] != '\'')
	{
		if (cmmd[tmp] == '\\' && cmmd[tmp + 1] == '\'')
			tmp++;
		tmp++;
	}
	if (cmmd[tmp] == '\'')
	{
		*qs = NO_QUOTE;
		*i = tmp;
		return (tmp);
	}
	return (-1);
}

void	quote_mng(char *cmmd, int *quote_state, int *end, int *i)
{
	if (cmmd[*i] == '\'')
		*end = simple_quo(cmmd, quote_state, i);
	else if (cmmd[*i] == '\"')
		*end = double_quo(cmmd, quote_state, i);
	if (*end == -1)
		syntax_err(3, NULL, '\0');
}
