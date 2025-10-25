/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_mng.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:45:08 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/25 20:48:07 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

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
