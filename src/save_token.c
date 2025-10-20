/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:33:13 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/20 17:56:28 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

/*t_bool	is_special_dollar(char *c, int len)
{
	if (ft_strncmp(str, "$?", len) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "$$", len) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "$!", len) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "$#", len) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "$@", len) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "$0", len) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "$1", len) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "${", 2) == 0 && ft_strrchr(str, '}') == &str[len])
		return (TRUE);
	return (FALSE);
}*/

static t_token_type	token_type(t_token *nd)
{
	char	*str;
	int		quo;
	int		len;

	str = nd->token;
	quo = nd->quote_type;
	len = ft_strlen(str);
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

t_bool	edge_quotes(char *str, char c)
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

t_bool	between_matchchr(char *str, char match, char avoid)
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

t_bool	no_quotes(char *str)
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

static t_token	*token_data(char *cmmd, int start, int end)
{
	char	*new_str;
	t_token	*new_token;

	new_str = ft_substr(cmmd, start, end - start + 1);
	if (!new_str)
		return (malloc_err(), NULL);
	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
	{
		free(new_str);
		return (malloc_err(), NULL);
	}
	new_token->token = new_str;
	new_token->quote_type = token_quo_type(new_token->token);
	new_token->type = token_type(new_token);
	return (new_token);
}

void	*new_token(t_list **head, char *cmmd, int start, int end)
{
	t_list	*new_nd;
	t_token	*nd_data;

	nd_data = token_data(cmmd, start, end);
	if (!nd_data)
		return (NULL);
	new_nd = ft_lstnew(nd_data);
	if (!new_nd)
		return (malloc_err(), del_t_token(nd_data), NULL);
	if (!*head)
		*head = new_nd;
	else
		ft_lstadd_back(head, new_nd);
	start = 0;
	end = 0;
	return (*head);
}

/* validos: $, |, <, >, ~
 * prohibidos: \, &, *, #, \n, \t
 * dudosos: "", '', {}, [], () */
t_bool	is_operand(char c, char next, int quo_st)
{
	if (quo_st == NO_QUOTE && (c == '&' || c == '*' || c == '#'
			|| c == '{' || c == '}' || c == '(' || c == ')'
			|| c == '[' || c == ']'))
		return (TRUE);
	if (quo_st != SIMPLE_QUOTE && c == '`')
		return (TRUE);
	else if (c == '\\' && (next == ' ' || !next) && quo_st != SIMPLE_QUOTE)
		return (TRUE);
	return (FALSE);
}

int	check_char(char *cmmd, int *quote_state, int *i)
{
	char	c[3];

	c[CURR] = cmmd[*i];
	c[NEXT] = cmmd[*i + 1];
	if (is_operand(c[CURR], c[NEXT], *quote_state))
		return (syntax_err(1, NULL, c[CURR]), -1);
	if (c[CURR] == '\\')
		(*i)++;
	return (1);
}

int	double_quo(char *cmmd, int *qs, int *i)
{
	int	tmp;

	tmp = *i + 1;
	*qs = DOUBLE_QUOTE;
	while (cmmd[tmp] && cmmd[tmp] != '\"')
	{
		if (cmmd[tmp] == '`')
			return (-1);
		if (cmmd[tmp] == '\\' && (cmmd[tmp + 1] == '\"' || cmmd[tmp + 1] == '`'))
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

int	simple_quo(char *cmmd, int *qs, int *i)
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
}

int	std_char(t_list	**head, char *cmmd, int *range)
{
	int	i;
	int	quote_state;

	i = 0;
	quote_state = NO_QUOTE;
	while (cmmd[i] && cmmd[i] != ' ' && quote_state == NO_QUOTE)
	{
		if (check_char(cmmd, &quote_state, &i) <= 0)
			return (ST_ERR);
		quote_mng(cmmd, &quote_state, &range[END], &i);
		if (range[END] == -1)
			return (syntax_err(3, NULL, '\0'), ST_ERR);
		i++;
	}
	if (range[END] == -1)
		return (ft_lstclear(head, &del_t_token), ST_ERR);
	if (!range[END] || range[END] != i)
		range[END] = i - 1;
	if (quote_state == NO_QUOTE)
		if (!new_token(head, cmmd, range[START], range[END]))
			return (ft_lstclear(head, &del_t_token), ST_ERR_MALLOC);
	return (i);
}

int	spc_char(char *cmmd)
{
	int	i;

	i = 0;
	while (cmmd[i] && (cmmd[i] == ' ' || cmmd[i] == '\t' || cmmd[i] == '\n'))
		i++;
	return (i);
}

int	cmmd_loop(t_list **head, char *cmmd, int *i)
{
	int	tmp;
	int	range[2];

	range[START] = 0;
	range[END] = 0;
	tmp = 0;
	if (!cmmd || !i)
		return (ST_ERR);
	if (cmmd[*i] == ' ')
		tmp = spc_char(&cmmd[*i]);
	else
		tmp = std_char(head, &cmmd[*i], range);
	if (tmp == ST_ERR || tmp == ST_ERR_MALLOC)
		return (ft_lstclear(head, &del_t_token), tmp);
	*i += tmp;
	return (ST_OK);
}

int	save_token(t_list **token_list, char *cmmd)
{
	int		i;
	t_state	state;
	t_list	*head;

	if (!cmmd)
		return (ST_ERR);
	i = 0;
	head = NULL;
	while (cmmd[i])
	{
		state = cmmd_loop(&head, cmmd, &i);
		if ((state == ST_ERR_MALLOC || state == ST_ERR))
			return (ft_lstclear(&head, del_t_token), state);
	}
	*token_list = head;
	return (ST_OK);
}
