/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal_mng.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:58:31 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/25 18:58:50 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

t_bool	is_new_state(char *str, int *quo_st, int read, char prev)
{
	int	curr_st;

	curr_st = *quo_st;
	if (read == 0 && curr_st == NO_QUOTE)
	{
		if (str[read] == '\'')
			*quo_st = SIMPLE_QUOTE;
		else if (str[read] == '\"')
			*quo_st = DOUBLE_QUOTE;
	}
	else if (curr_st == NO_QUOTE)
	{
		if (str[read] == '\'' && prev != '\\')
			*quo_st = SIMPLE_QUOTE;
		else if (str[read] == '\"' && prev != '\\')
			*quo_st = DOUBLE_QUOTE;
	}
	else
		*quo_st = NO_QUOTE;
	if (curr_st != *quo_st)
		return (TRUE);
	return (FALSE);
}

void	rm_dou_quo_and_backslash(char **str, int *quo_st, int *read, int *write)
{
	char	c[3];

	(*read)++;
	c[PREV] = '\0';
	while ((*str)[*read])
	{
		c[NEXT] = (*str)[*read + 1];
		if ((*str)[*read] == '\\'
			&& (c[NEXT] == '`' || c[NEXT] == '$' || c[NEXT] == '\"' ))
		{
			c[PREV] = (*str)[*read];
			(*read)++;
		}
		if (!(*str)[*read] || (c[PREV] != '\\' && (*str)[*read] == '\"'))
			break ;
		(*str)[*write] = (*str)[*read];
		(*write)++;
		c[PREV] = (*str)[*read];
		(*read)++;
	}
	(*read)++;
	is_new_state(*str, quo_st, *read, c[PREV]);
}

void	rm_sim_quo_and_backslash(char **str, int *quo_st, int *read, int *write)
{
	char	prev;
	t_bool	is_escaped;

	(*read)++;
	prev = '\0';
	if ((*str)[*read] != '\'')
		is_escaped = TRUE;
	else
		is_escaped = FALSE;
	while ((*str)[*read] && is_escaped)
	{
		(*str)[*write] = (*str)[*read];
		(*write)++;
		prev = (*str)[*read];
		(*read)++;
		if ((*str)[*read] == '\'' && prev != '\\')
			is_escaped = FALSE;
	}
	(*read)++;
	is_new_state(*str, quo_st, *read, prev);
}

void	rm_backslash(char **str, int *quo_st, int *read, int *write)
{
	char	prev;
	t_bool	is_even;

	prev = '\0';
	if (is_new_state(*str, quo_st, *read, prev))
		return ;
	is_even = FALSE;
	while (*quo_st == NO_QUOTE && (*str)[*read])
	{
		if ((*str)[*read] != '\\'
			|| ((*str)[*read] == '\\' && prev == '\\' && !is_even))
		{
			if ((*str)[*read] == '\\' && prev == '\\')
				is_even = TRUE;
			(*str)[*write] = (*str)[*read];
			(*write)++;
		}
		else if ((*str)[*read] == '\\' && prev == '\\' && is_even)
			is_even = FALSE;
		prev = (*str)[*read];
		(*read)++;
		if (is_new_state(*str, quo_st, *read, prev))
			return ;
	}
}

void	rm_quote_mng(char **str)
{
	int		write;
	int		read;
	int		quo_st;

	read = 0;
	write = 0;
	quo_st = NO_QUOTE;
	while ((*str)[read] != '\0')
	{
		if (quo_st == NO_QUOTE)
			rm_backslash(str, &quo_st, &read, &write);
		else if (quo_st == SIMPLE_QUOTE)
			rm_sim_quo_and_backslash(str, &quo_st, &read, &write);
		else if (quo_st == DOUBLE_QUOTE)
			rm_dou_quo_and_backslash(str, &quo_st, &read, &write);
	}
	(*str)[write] = '\0';
}
