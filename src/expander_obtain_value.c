/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_obtain_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:42:00 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/25 20:53:36 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_bool	is_special_dollar(char c)
{
	if (c == '?' || c == '$' || c == '!' || c == '#' || c == '@'
		|| c == '0' || c == '1')
		return (TRUE);
	return (FALSE);
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
