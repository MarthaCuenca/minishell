/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:13:08 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/03 15:58:31 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	fill_dest(char *dest, char **values, char *str)
{
	int		i;
	int		j;
	int		k;
	int		value_len;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] && (str[i] != '\'' && str[i] != '\"'))
			dest[k++] = str[i++];
		if (!str[i])
			break ;
		value_len = ft_strlen(values[j]);
		ft_memcpy(&dest[k], values[j], value_len);
		i += value_len + 2;
		j++;
		k += value_len;
	}
}

int	how_many_quote(char *str)
{
	int	simple;
	int	dou;
	int	count;

	simple = count_c_char(str, '\'');
	dou = count_c_char(str, '\"');
	count = (simple + dou) / 2;
	return (count);
}

int	obtain_start(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] != '\'' && str[i] != '\"'))
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

int	obtain_end(char *str)
{
	int	i;
	int	end;
	int	quote_state;

	i = 0;
	end = 0;
	quote_state = NO_QUOTE;
	quote_mng(str, &quote_state, &end, &i);
	if (end == -1)
		return (-1);
	return (i);
}

t_bool	value_range(char *tmp, int *range)
{
	range[START] = obtain_start(tmp);
	tmp += range[START];
	range[END] = obtain_end(tmp);
	if (range[START] == -1 || range[END] == -1)
		return (FALSE);
	return (TRUE);
}

char	**obtain_quote_values(char *str)
{
	int		j;
	int		range[2];
	char	*tmp;
	char	**values;

	values = ft_calloc((how_many_quote(str) + 1), sizeof(char *));
	if (!values)
		return (malloc_err(), NULL);
	j = 0;
	tmp = str;
	while (tmp)
	{
		if (!value_range(tmp, range))
			break ;
		values[j] = ft_substr(str, range[START] + 1, range[END] - 1);
		if (!values[j])
			return (arg_err(), ft_free_2p(values), NULL);
		tmp += range[END] + 1;
		j++;
	}
	values[j] = NULL;
	return (values);
}

/*char	**obtain_quote_values(char *str)
{
	int		j;
	int		range[2];
	char	*tmp;
	char	**values;

	values = ft_calloc((how_many_quote(str) + 1), sizeof(char *));
	if (!values)
		return (arg_err(), NULL);
	j = 0;
	tmp = str;
	while (tmp)
	{
		range[START] = obtain_start(tmp);
		tmp += range[START];
		range[END] = obtain_end(tmp);
		if (range[START] == -1 || range[END] == -1)
			break ;
		values[j] = ft_substr(str, range[START] + 1, range[END] - 1);
		if (!values[j])
			return (arg_err(), ft_free_2p(values), NULL);
		tmp += range[END] + 1;
		j++;
	}
	values[j] = NULL;
	return (values);
}*/

char	*delete_quote(char *str)
{
	char	*dest;
	char	**values;

	dest = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!dest)
		return (arg_err(), NULL);
	values = obtain_quote_values(str);
	if (!values)
		return (free(dest), NULL);
	fill_dest(dest, values, str);
	ft_free_2p(values);
	return (dest);
}

t_bool	rm_quote_mng(char **str)
{
	char	*new_str;
	t_quote	quo_ty;

	quo_ty = token_quo_type(*str);
	if (quo_ty != NO_QUOTE)
	{
		new_str = delete_quote(*str);
		if (!new_str)
			return (FALSE);
		ft_swap_str(&new_str, str);
		free(new_str);
	}
	return (TRUE);
}

t_bool	dir_quote_rm_loop(t_redir *dir)
{
	int	j;

	j = 0;
	if (!dir)
		return (TRUE);
	while (dir[j].file)
	{
		if (!rm_quote_mng(&dir[j].file))
			return (FALSE);
		j++;
	}
	return (TRUE);
}

t_bool	arg_rm_quote_loop(char **arg)
{
	int	j;

	j = 0;
	if (!arg)
		return (TRUE);
	while (arg[j])
	{
		if (!rm_quote_mng(&arg[j]))
			return (FALSE);
		j++;
	}
	return (TRUE);
}

t_bool	quote_removal(t_list **pars)
{
	t_list	*tmp;
	t_cmmd	*curr_cmmd;
	t_redir	*dir;
	char	**arg;

	if (!pars)
		return (malloc_err(), FALSE);
	tmp = *pars;
	while (tmp)
	{
		curr_cmmd = (t_cmmd *)tmp->content;
		arg = curr_cmmd->cmmd;
		dir = (t_redir *)curr_cmmd->redir;
		if (!arg_rm_quote_loop(arg))
			return (FALSE);
		if (!dir_quote_rm_loop(dir))
			return (FALSE);
		tmp = tmp->next;
	}
	return (TRUE);
}
