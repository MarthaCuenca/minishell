/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:56:20 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/08/27 16:40:34 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>


/*int	expansion_len(t_token *token)
{
	int		len;
	int		quote;
	char	*exp_var_name;
	char	*sd[2];

	if (!token)
		return (0);
	quote = (int)token->quote_type;
	exp_var_name = (char *)token->token;
	if (quote == NO_QUOTE)
		len = ft_strlen(exp_var_name) - 1;
	else
	{
		sd[START] = ft_strchr(exp_var_name, '$') + 1;
		sd[END] = ft_strchr(sd[START], ' ');
		if (!sd[END])
			sd[END] = ft_strchr(sd[START], '\"');
		sd[END] -= 1;
		len = sd[END] - sd[START] + 1;
	}
	return (len);
}*/

/*int	expansion_len(char *dollar, char **sd)
{
	int		len;

	if (!dollar || !sd)
		return (0);
	sd[START] = ft_strchr(dollar, '$') + 1;
	sd[END] = ft_strchr(sd[START], ' ');
	if (!sd[END])
		sd[END] = ft_strchr(sd[START], '\"');
	if (!sd[END])
		sd[END] = ft_strchr(sd[START], '$');
	if (!sd[END])
		sd[END] = ft_strchr(sd[START], '\0');
	sd[END] -= 1;
	len = sd[END] - sd[START] + 1;
	return (len);
}*/

int	expansion_len(char *start)
{
	int		len;
	char	*end;

	if (!start)
		return (0);
	end = ft_strchr(start, ' ');
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
	if (!dollar)
		return (FALSE);
	else if (!dollar[1])
			return (FALSE);
	else if (dollar[1] == ' ' || dollar[1] == '\t' || dollar[1] == '\n')
			return (FALSE);
	return (TRUE);
}

void	exp_no_quote(t_token **tk, char **values)//AQUI 2
{
	char	*value;

	if (!*tk || !values)
		return ;

	free((*tk)->token);
	value = ft_strdup(values[0]);
	(*tk)->token = value;
}

void	fill_new_exp_double_quote(char *dest, char *tk, char **values)
{
	int	i;//dest
	int	j;//values
	int	k;//token
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
		dest[i] = tk[k];
		i++;
		k++;
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
	large_str = (char *)malloc((len + 1) * sizeof(char));
	if (!large_str)
		return ;
	fill_new_exp_double_quote(large_str, (*tk)->token, values);
	free((*tk)->token);
	(*tk)->token = large_str;
//	printf("%d\n", len);
}

char	*get_env_value_v2(char *env_match, int env_var_len)
{
	int		value_len;
	int		start;
	char	*value;

	if (!env_match || !env_var_len)
		return (NULL);
	start = env_var_len + 1;
	value_len = ft_strlen(&env_match[start]);
	value = ft_substr(env_match, start, value_len);
	if (!value)
		return (NULL);
	return (value);
}

char	*get_env_value_v1(char *env_match)
{
	char	*equal;
	char	*start;
	char	*value;

	if (!env_match )
		return (NULL);
	equal = ft_strchr(env_match, '=');
	if (!equal)
		return (NULL);
	if (equal[1])//Un '=' puede forma parte de nombre de la variable?
		start = &equal[1];
	value = ft_strdup(start);
	if (!value)
		return (NULL);
	return (value);
}

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

	if(!str || !tk_len || !env )
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

char		*obtain_env_var_value(char *dollar, t_list *env)
{
	unsigned int	len;
	char	*sd[2];
	char	*env_value;
	t_list	*match;

	sd[START] = dollar + 1;
	len = expansion_len(sd[START]);
	sd[END] = dollar + len;
	match = check_env_var(sd[START], len, env);
	env_value = NULL;
	if (!match)	
		return (NULL);
	//env_value = get_env_value_v1((char *)match->content);OJO! usa el que mas te guste, ambos funcionan
	env_value = get_env_value_v2((char *)match->content, len);
	if (!env_value)
		return (NULL);
	return (env_value);
}

/*char		*obtain_env_var_value(char *dollar, t_list *env)
{
	unsigned int	len;
	char	*sd[2];
	char	*env_value;
	t_list	*match;

	len = expansion_len(dollar, sd);
	match = check_env_var(sd[START], len, env);
	env_value = NULL;
	if (!match)	
		return (NULL);
	//env_value = get_env_value_v1((char *)match->content);OJO! usa el que mas te guste, ambos funcionan
	env_value = get_env_value_v2((char *)match->content, len);
	if (!env_value)
		return (NULL);
	return (env_value);
}*/

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

char **exp_values(t_token *tk, t_list *env)
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
			exp_str[j] = obtain_env_var_value(check_point, env);
			if (!exp_str[j])
				return (ft_free_2p(exp_str), NULL);
		}
		check_point++;
		j++;
	}
	return (exp_str);
}

t_bool exp_mng(t_token **tk, t_list *env)
{
	char	**values;

	if (!*tk || !env)
		return (FALSE);
	values = exp_values(*tk, env);
	if (!values)
		return (FALSE);
	if (!*values)
		return (ft_free_2p(values), FALSE);
	/* si es DOUBLE_QUOTE todo va a 1 token
	 * si es NO_QUOTE van separados*/
	if ((*tk)->quote_type == NO_QUOTE)
		exp_no_quote(tk, values);//AQUI, FALTA HACER TODO ESTO
	else if ((*tk)->quote_type == DOUBLE_QUOTE)
		exp_double_quote(tk, values);//AQUI 3, cino en tamano o lo dejo grande?
	ft_free_2p(values);
	return (TRUE);
}

t_bool expander(t_list **lex, t_list *env)
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
			if (!exp_mng(&tk, env))
				return (FALSE);/*Puede fallar el mng?*/
			//env_var = check_env_var((t_token *)tmp->content, env);
		tmp = tmp->next;
	}
	print_tokens(*lex, TRUE, 0);
	return (TRUE);
}
