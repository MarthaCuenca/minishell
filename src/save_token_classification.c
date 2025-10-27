/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_token_classification.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:30:56 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/27 18:36:05 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	token_type(t_token *nd)
{
	char	*str;
	int		quo;

	str = nd->token;
	quo = nd->quote_type;
	if (ft_strcmp(str, "<<") == 0 && quo == NO_QUOTE)
		return (REDIR);
	else if (ft_strcmp(str, ">>") == 0 && quo == NO_QUOTE)
		return (REDIR);
	else if (ft_strcmp(str, "<") == 0 && quo == NO_QUOTE)
		return (REDIR);
	else if (ft_strcmp(str, ">") == 0 && quo == NO_QUOTE)
		return (REDIR);
	else if (ft_strcmp(str, "|") == 0 && quo == NO_QUOTE)
		return (PIPE);
	return (WORD);
}

static t_bool	edge_quotes(char *str, char c)
{
	int	i;
	int	len;

	if (!str || !c)
		return (FALSE);
	i = 1;
	len = ft_strlen(str);
	if (str[0] != c && str[len] != c)
		return (FALSE);
	while (str[i] && i < len - 1)
	{
		if (str[i] == c)
		{
			if (i > 0 && str[i - 1] != '\\')
				return (FALSE);
			i++;
		}
		i++;
	}
	return (TRUE);
}

static t_bool	between_matchchr(char *str, char match, char avoid)
{
	int		i;
	int		quotes_inside;
	t_bool	open;

	open = FALSE;
	quotes_inside = FALSE;
	i = 0;
	while (str[i])
	{
		if (i > 0 && str[i] == match && str[i - 1] == '\\')
			i++;
		if (str[i] == avoid && open == FALSE)
			return (FALSE);
		if (str[i] == match)
		{
			quotes_inside = TRUE;
			if (!open)
				open = TRUE;
			else
				open = FALSE;
		}
		i++;
	}
	return (quotes_inside);
}

static t_bool	no_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			if (i > 0 && str[i - 1] != '\\')
				return (FALSE);
		i++;
	}
	return (TRUE);
}

t_quote	token_quo_type(char *str)
{
	if (no_quotes(str))
		return (NO_QUOTE);
	else if (edge_quotes(str, '\''))
		return (SIMPLE_QUOTE);
	else if (between_matchchr(str, '\'', '\"'))
		return (SIMPLE_QUOTE_IN);
	else if (edge_quotes(str, '\"'))
		return (DOUBLE_QUOTE);
	else if (between_matchchr(str, '\"', '\''))
		return (DOUBLE_QUOTE_IN);
	return (MIXED_QUOTE);
}
