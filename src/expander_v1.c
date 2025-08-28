/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_v1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:56:20 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/08/28 19:48:33 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

int	expansion_len(char *start)
{
	int		len;
	char	*end;

	if (!start)
		return (0);
	end = ft_strchr(start, ' ');
	if (!end && is_special_dollar(start, 2))
		end = &start[2];
	if (!end)
		end = ft_strchr(start, '\"');
	if (!end)
		end = ft_strchr(start, '$');
	if (!end)
		end = ft_strchr(start, '\0');
	end -= 1;
	len = end - start + 1;
	return (len);
}

t_bool	is_dollar_valid(char *dollar)
{
	char	symbols[4];

	symbols[0] = ' ';
	symbols[1] = '\t';
	symbols[2] = '\n';
	symbols[3] = '\"';
	if (!dollar)
		return (FALSE);
	else if (!dollar[1])
		return (FALSE);
	else if (dollar[1]
		&& is_c_symbol(dollar[1], symbols))
		//&& (dollar[1] == ' ' || dollar[1] == '\t' || dollar[1] == '\n' || dollar[1] == '\"'))
		return (FALSE);
	return (TRUE);
}

void	exp_no_quote(t_token **tk, char **values)
{
	char	*value;

	if (!*tk || !values)
		return ;
	free((*tk)->token);
	value = ft_strdup(values[0]);
	(*tk)->token = value;
}

/*i dest
 * j values
 * k token*/
void	fill_new_exp_double_quote(char *dest, char *tk, char **values)
{
	int	i;
	int	j;
	int	k;
	int	value_len;

	i = 0;
	j = 0;
	k = 0;
	while (tk[k])
	{
		if (tk[k] == '$' && is_dollar_valid(&tk[k]))
		{
			k += expansion_len(&tk[k]);
			value_len = ft_strlen(values[j]);
			ft_memcpy(&dest[i], values[j], value_len);
			i += value_len;
			j++;
		}
		else
		{
			dest[i] = tk[k];
			i++;
			k++;
		}
	}
	dest[i] = '\0';
}

void	exp_double_quote(t_token **tk, char **values)
{
	int		j;
	int		len;
	char	*large_str;

	if (!*tk || !values)
		return ;
	j = 0;
	len = ft_strlen((*tk)->token);
	while (values[j])
		len += ft_strlen(values[j++]);
	large_str = (char *)ft_calloc((len + 1), sizeof(char));
	if (!large_str)
		return ;
	fill_new_exp_double_quote(large_str, (*tk)->token, values);
	free((*tk)->token);
	(*tk)->token = large_str;
}

char	*get_env_value_v2(t_list *env_match, int env_var_len)
{
	int		value_len;
	int		start;
	char	*tmp;
	char	*value;

	if (env_match)
	{
		tmp = (char *)env_match->content;
		start = env_var_len + 1;
		value_len = ft_strlen(&tmp[start]);
		value = ft_substr(tmp, start, value_len);
	}
	else
		value = (char *)ft_calloc(1, sizeof(char));
	if (!value)
		return (NULL);
	return (value);
}

/*char	*get_env_value_v1(t_list *env_match)
{
	char	*equal;
	char	*start;
	char	*value;
	char	*tmp;

	if (env_match)
	{
		tmp = (char *)match->content;
		equal = ft_strchr(env_match, '=');
		if (!equal)
			return (NULL);
		if (equal[1])
			start = &equal[1];
		value = ft_strdup(start);
	}
	else
		value = (char *)ft_calloc(1, sizeof(char));
	if (!value)
		return (NULL);
	return (value);
}*/

int	var_len(char *str)
{
	int		i;
	char	*equal;

	if (!str)
		return (0);
	i = 0;
	equal = ft_strchr(str, '=');
	if (!equal)
		return (ft_strlen(str));
	while (str[i] && str[i] != *equal)
		i++;
	return (i);
}

t_list	*check_env_var(char *str, int tk_len, t_list *env)
{
	int		env_var_len;
	int		check;
	char	*var;
	t_list	*tmp;

	if (!str || !tk_len || !env)
		return (NULL);
	check = 0;
	tmp = env;
	while (tmp)
	{
		var = (char *)tmp->content;
		env_var_len = var_len(var);
		check = ft_strncmp(str, var, tk_len);
		if (check == 0 && tk_len == env_var_len)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

/*
 * env_value = get_env_value_v1(match);
 * env_value = get_env_value_v2(match, len);
 * */
char	*obtain_env_var_value(char *dollar, t_list *env, t_cmmd *return_value)
{
	int		len;
	char	*sd[2];
	char	*env_value;
	t_list	*match;

	if (dollar[1] && dollar[1] == '?')
	{
		if (return_value)
			env_value = ft_itoa(return_value->r);
		else
			env_value = ft_strdup("0");
		if (!env_value)
			return (NULL);
		return (env_value);
	}
	sd[START] = dollar + 1;
	len = expansion_len(sd[START]);
	sd[END] = dollar + len;
	match = check_env_var(sd[START], len, env);
	env_value = get_env_value_v2(match, len);
	if (!env_value)
		return (NULL);
	return (env_value);
}

int	count_dollar(char *exp_tk)
{
	int		count;
	char	*check_point;

	count = 0;
	check_point = exp_tk;
	while (check_point)
	{
		check_point = ft_strchr(check_point, '$');
		if (!check_point)
			break ;
		if (is_dollar_valid(check_point))
			count++;
		check_point++;
	}
	return (count);
}

char	**exp_values(t_token *tk, t_list *env, t_cmmd *return_value)
{
	int		j;
	int		n;
	char	**exp_str;
	char	*check_point;

	j = 0;
	n = count_dollar(tk->token);
	exp_str = (char **)ft_calloc(n + 1, sizeof(char *));
	if (!exp_str)
		return (NULL);
	check_point = tk->token;
	while (j < n)
	{
		check_point = ft_strchr(check_point, '$');
		if (check_point && is_dollar_valid(check_point))
		{
			exp_str[j] = obtain_env_var_value(check_point, env, return_value);
			if (!exp_str[j])
				return (ft_free_2p(exp_str), NULL);
		}
		check_point++;
		j++;
	}
	return (exp_str);
}

t_bool	exp_mng(t_token **tk, t_list *env, t_cmmd *return_value)
{
	char	**values;

	if (!tk || !env)
		return (FALSE);
	values = exp_values(*tk, env, return_value);
	if (!values)
		return (FALSE);
	if (*values)
	{
		if ((*tk)->quote_type == NO_QUOTE)
			exp_no_quote(tk, values);
		else if ((*tk)->quote_type == DOUBLE_QUOTE)
			exp_double_quote(tk, values);
	}
	ft_free_2p(values);
	return (TRUE);
}

t_bool	expander(t_list **lex, t_list *env, t_cmmd *return_value)
{
	t_token	*tk;
	t_list	*tmp;

	tmp = *lex;
	if (!env || !*lex)
		return (FALSE);
	while (tmp)
	{
		tk = ((t_token *)tmp->content);
		if (tk->type == EXP)
			if (!exp_mng(&tk, env, return_value))
				return (FALSE);
		tmp = tmp->next;
	}
	print_tokens(*lex, TRUE, 0);
	return (TRUE);
}
