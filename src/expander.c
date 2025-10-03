/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:56:52 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/03 15:58:11 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

int	varname_len_in_str(char *start)
{
	int		i;
	char	*end;
	char	*symbols[6];

	i = 0;
	end = NULL;
	symbols[0] = ft_strchr(start, ' ');
	symbols[1] = ft_strchr(start, '?');
	symbols[2] = ft_strchr(start, '\'');
	symbols[3] = ft_strchr(start, '\"');
	symbols[4] = ft_strchr(start, '$');
	symbols[5] = ft_strchr(start, '\0');
	if (!start)
		return (0);
	while (i < 7)
	{
		if (symbols[i] && (!end || symbols[i] < end))
			end = symbols[i];
		i++;
	}
	if (!end)
		return (0);
	end -= 1;
	return (end - start + 1);
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
	while (&str[i] != dollar)
	{
		if (str[i] == '\\')
			i += 2;
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

t_bool	is_dollar_valid(char *str, char *dollar)
{
	char	symbols[4];
	t_quote	quote_state;

	if (!dollar)
		return (FALSE);
	symbols[0] = ' ';
	symbols[1] = '\t';
	symbols[2] = '\n';
	symbols[3] = '\"';
	quote_state = NO_QUOTE;
	check_state(str, dollar, &quote_state);
	if (quote_state == SIMPLE_QUOTE)
		return (FALSE);
	else if (!dollar[1])
		return (FALSE);
	else if (dollar[1] && is_c_symbol(dollar[1], symbols))
		return (FALSE);
	return (TRUE);
}

int	count_dollar(char *str)
{
	int		count;
	char	*check_point;

	count = 0;
	check_point = str;
	while (check_point)
	{
		check_point = ft_strchr(check_point, '$');
		if (!check_point)
			break ;
		if (is_dollar_valid(str, check_point))
			count++;
		check_point++;
	}
	return (count);
}

void	fill_new_str(char *dest, char **values, char *str)
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
		if (str[i] == '$' && is_dollar_valid(str, &str[i]))
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

char	*exchange_exp_var(char **values, char *str)
{
	int		j;
	int		len;
	char	*new_str;

	j = 0;
	len = ft_strlen(str);
	while (values[j])
		len += ft_strlen(values[j++]);
	new_str = (char *)ft_calloc((len + 1), sizeof(char));//AQUI
	if (!new_str)
		return (malloc_err(), NULL);
	fill_new_str(new_str, values, str);
	return (new_str);
}

char	*get_env_value(t_list *match, int var_len)
{
	int		value_len;
	int		start;
	char	*tmp;
	char	*value;

	if (match)
	{
		tmp = (char *)match->content;
		start = var_len + 1;
		value_len = ft_strlen(&tmp[start]);
		value = ft_substr(tmp, start, value_len);
	}
	else
		value = (char *)ft_calloc(1, sizeof(char));
	if (!value)
		return (malloc_err(), NULL);
	return (value);
}

t_list	*check_env_var(char *str, int in_len, t_list *env)
{
	int		env_varname_len;
	int		check;
	char	*var;
	t_list	*tmp;

	if (!str || !in_len || !env)
		return (arg_err(), NULL);
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

char	*obtain_env_var_value(t_env *env, char *dollar)
{
	int		in_len;
	char	*sd[2];
	char	*env_value;
	t_list	*match;

	if (dollar[1] && dollar[1] == '?')
	{
		if (env->r)
			env_value = ft_itoa(env->r);
		else
			env_value = ft_strdup("0");
		if (!env_value)
			return (malloc_err(), NULL);
		return (env_value);
	}
	sd[START] = dollar + 1;
	in_len = varname_len_in_str(sd[START]);
	sd[END] = dollar + in_len;
	match = check_env_var(sd[START], in_len, (t_list *)env->vars);
	env_value = get_env_value(match, in_len);
	if (!env_value)
		return (NULL);
	return (env_value);
}

char	**exp_values(t_env *env, char *str, int n_dollar)
{
	int		j;
	char	**exp_str;
	char	*check_point;

	j = 0;
	exp_str = (char **)ft_calloc(n_dollar + 1, sizeof(char *));
	if (!exp_str)
		return (malloc_err(), NULL);
	check_point = str;
	while (j < n_dollar)
	{
		check_point = ft_strchr(check_point, '$');
		if (check_point && is_dollar_valid(str, check_point))
		{
			exp_str[j] = obtain_env_var_value(env, check_point);
			if (!exp_str[j])
				return (malloc_err(), ft_free_2p(exp_str), NULL);
		}
		check_point++;
		j++;
	}
	exp_str[j] = NULL;
	return (exp_str);
}

t_bool	exp_mng(t_env *env, char **str)
{
	int		n_dollar;
	char	**values;
	char	*new_str;

	n_dollar = count_dollar(*str);
	if (n_dollar == 0)
		return (TRUE);
	values = exp_values(env, *str, n_dollar);
	if (!values)
		return (FALSE);
	new_str = exchange_exp_var(values, *str);
	if (!new_str)
		return (ft_free_2p(values), FALSE);
	ft_swap_str(&new_str, str);
	free(new_str);
	ft_free_2p(values);
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
		if (!exp_mng(env, &dir[j].file))
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
		if (!exp_mng(env, &arg[j]))
			return (FALSE);
		j++;
	}
	return (TRUE);
}

t_bool	expander(t_env *env, t_list **pars)
{
	t_list	*tmp;
	t_cmmd	*curr_cmmd;
	t_redir	*dir;
	char	**arg;

	if (!pars || !env)
		return (arg_err(), FALSE);
	tmp = *pars;
	while (tmp)
	{
		curr_cmmd = (t_cmmd *)tmp->content;
		arg = curr_cmmd->cmmd;
		dir = (t_redir *)curr_cmmd->redir;
		if (!arg_loop(env, arg))
			return (FALSE);
		if (!dir_loop(env, dir))
			return (FALSE);
		tmp = tmp->next;
	}
	return (TRUE);
}
