/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:56:52 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/25 18:05:14 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

//AQUI falta expansiones de multiples dollars y que una var_no_existe + var_existe me poner 1 espacio

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

int	ft_is_samealloc_diffpos(char *str, char *ptr)
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

t_bool	is_special_dollar(char c)
{
	if (c == '?' || c == '$' || c == '!' || c == '#' || c == '@'
		|| c == '0' || c == '1')
		return (TRUE);
	return (FALSE);
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
	/*else if (!valid_env_varname_syntax(dollar + 1, len)
		&& (dollar[1] && is_special_dollar(dollar[1]) == TRUE))
		return (FALSE);*/
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
			//if (values[j][0] != '\0')
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

char	*get_env_value(t_list *match, int var_len)
{
	char	*tmp;
	char	*value;

	if (match)
	{
		tmp = (char *)match->content;
		value = tmp + var_len + 1;
	}
	else
		value = "";
	return (value);
}

t_list	*check_env_var(char *str, int in_len, t_list *env)
{
	int		env_varname_len;
	int		check;
	char	*var;
	t_list	*tmp;

	if (!str || !in_len || !env)
		return (NULL);
	check = 0;
	tmp = env;
	while (tmp)
	{
		var = (char *)tmp->content;
		env_varname_len = env_key_len(var, '=');
		check = ft_strncmp(str, var, in_len);
		if (check == 0 && in_len == env_varname_len)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

/*int	ft_count_digits(long int n)
{
	int	count;

	if (n > 2147483647 || n < -2147483647)
		return (0);
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	count = 0;
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_static_itoa(char *dest, int size, long int n)
{
	int	digits;

	if (!dest || size <= 0 || size > 12 || n > 2147483647 || n < -2147483647)
		return (NULL);
	digits = ft_count_digits(n);
	if (n < 0)
	{
		n *= -1;
		dest[0] = '-';
		digits++;
	}
	if (digits >= size)
	{
		dest[0] = '\0';
		return (NULL);
	}
	dest[digits] = '\0';
	while (digits-- > 0)
	{
		dest[digits] = (n % 10) + '0';
		n = n / 10;
	}
	return (dest);
}*/

char	*obtain_special_env_var_value(t_env *env, char b[], char dollar)
{
	char	*env_value;

	if (dollar == '?')
		env_value = ft_static_itoa(b, 4, env->r);
	else
		env_value = "";
	return (env_value);
}

char	*obtain_env_var_value(t_env *env, char b[], char *dollar)
{
	int		in_len;
	char	*sd[2];
	char	*env_value;
	t_list	*match;

	if (dollar && is_special_dollar(dollar[0]))
	{
		env_value = obtain_special_env_var_value(env, b, dollar[0]);
		if (!env_value)
			return (NULL);
		return (env_value);
	}
	sd[START] = dollar;
	in_len = varname_len_in_str(sd[START]);
	sd[END] = dollar + in_len;
	match = check_env_var(sd[START], in_len, (t_list *)env->vars);
	env_value = get_env_value(match, in_len);
	return (env_value);
}

char	**exp_values(t_env *env, char b[], char *str, t_bool is_heredoc)
{
	int		j;
	int		n_dollar;
	char	**exp_str;
	char	*checkpoint;

	j = 0;
	n_dollar = count_dollar(str, is_heredoc);
	exp_str = (char **)ft_calloc(n_dollar + 1, sizeof(char *));
	if (!exp_str)
		return (malloc_err(), NULL);
	checkpoint = str;
	while (j < n_dollar)
	{
		checkpoint = ft_strchr(checkpoint, '$');
		if (checkpoint && is_dollar_valid(str, checkpoint, is_heredoc))
			exp_str[j++] = obtain_env_var_value(env, b, checkpoint + 1);
		if (is_special_dollar(checkpoint[1]) == TRUE)
			checkpoint++;
		checkpoint++;
	}
	exp_str[j] = NULL;
	return (exp_str);
}

t_bool	exp_mng(t_env *env, char **str, t_bool is_heredoc)
{
	char	**values;
	char	*new_str;
	char	b[4];

	values = exp_values(env, b, *str, is_heredoc);
	if (!values)
		return (FALSE);
	new_str = exchange_exp_var(values, *str, is_heredoc);
	if (!new_str)
		return (free(values), FALSE);
	ft_swap_str(&new_str, str);
	free(new_str);
	free(values);
	return (TRUE);
}

t_bool	dir_loop(t_env *env, t_redir *dir)
{
	int	j;

	j = 0;
	if (!dir)
		return (TRUE);
	while (dir[j].file)
	{
		if (dir[j].type != HEREDOC)
			if (!exp_mng(env, &dir[j].file, FALSE))
				return (FALSE);
		j++;
	}
	return (TRUE);
}

t_bool	arg_loop(t_env *env, char **arg)
{
	int	j;

	j = 0;
	if (!arg)
		return (TRUE);
	while (arg[j])
	{
		if (!exp_mng(env, &arg[j], FALSE))
			return (FALSE);
		j++;
	}
	return (TRUE);
}

int	expander(t_env *env, t_list **pars)
{
	t_list	*tmp;
	t_cmmd	*curr_cmmd;
	t_redir	*dir;
	char	**arg;

	if (!pars || !env)
		return (ST_ERR);
	tmp = *pars;
	while (tmp)
	{
		curr_cmmd = (t_cmmd *)tmp->content;
		arg = curr_cmmd->cmmd;
		dir = (t_redir *)curr_cmmd->redir;
		if (!arg_loop(env, arg))
			return (ST_ERR_MALLOC);
		if (!dir_loop(env, dir))
			return (ST_ERR_MALLOC);
		tmp = tmp->next;
	}
	return (ST_OK);
}
