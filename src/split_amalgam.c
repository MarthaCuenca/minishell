/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_amalgam.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:51:58 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/27 18:50:59 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void	is_inequality_symbols(char *str, int *quote_state, int *end, int *i)
{
	if (*quote_state != NO_QUOTE)
		return ;
	if (ft_strstr(&str[*i], "<<<") || ft_strstr(&str[*i], ">>>"))
	{
		*end = -1;
		syntax_err(1, NULL, str[*i + 2]);
	}
	else
	{
		if (ft_strrstr(&str[*i], "<<") || ft_strstr(&str[*i], ">>"))
			(*i)++;
		(*i)++;
		*end = *i - 1;
	}
}

static void	is_underscore(char *str, int *end, int *i)
{
	if (str[*i] == '|')
		(*i)++;
	*end = *i - 1;
}

static void	is_other(char *str, int *quote_state, int *end, int *i)
{
	while (str[*i] && str[*i] != '<' && str[*i] != '>' && str[*i] != '|')
	{
		if (str[*i] == '\\' && (str[*i + 1] == '\'' || str[*i + 1] == '\"'))
			(*i)++;
		else if (str[*i] == '\'' || str[*i] == '\"')
			quote_mng(str, quote_state, end, i);
		if (*end == -1)
			return ;
		(*i)++;
	}
	*end = *i - 1;
}

static int	start_end_amalgam(char *str, int *quote_state, int *sd, int *i)
{
	sd[START] = *i;
	if (str[*i] == '<' || str[*i] == '>')
		is_inequality_symbols(str, quote_state, &sd[END], i);
	else if (str[*i] == '|')
		is_underscore(str, &sd[END], i);
	else
		is_other(str, quote_state, &sd[END], i);
	if (sd[END] == -1)
		return (-1);
	return (1);
}

t_state	split_amalgam(t_list *tk, t_list **head)
{
	int		i;
	int		sd[2];
	int		quote_state;
	char	*str;

	i = 0;
	quote_state = NO_QUOTE;
	str = ((t_token *)tk->content)->token;
	sd[START] = 0;
	sd[END] = 0;
	while (str[i])
	{
		start_end_amalgam(str, &quote_state, sd, &i);
		if (sd[END] == -1)
			return (ST_ERR);
		if (!new_token(head, str, sd[START], sd[END]))
			return (ft_lstclear(head, &del_t_token), ST_ERR_MALLOC);
	}
	return (ST_OK);
}
