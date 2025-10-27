/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:49:26 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/27 13:19:22 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static t_state	bi_export_new_env_var_value(t_list **node, char *str)
{
	char	*tmp;
	char	*dup;

	tmp = (char *)(*node)->content;
	dup = ft_strdup(str);
	if (!dup)
		return (ST_ERR);
	(*node)->content = dup;
	free(tmp);
	return (ST_OK);
}

static t_state	bi_export_new_var(t_list **vars, char *str)
{
	char	*equal_char;
	char	*new_str;
	t_list	*new_node;

	equal_char = ft_strchr(str, '=');
	if (equal_char && !equal_char[1])
		new_str = ft_strjoin(str, "\"\"");
	else
		new_str = ft_strdup(str);
	if (!new_str)
		return (ST_ERR);
	new_node = ft_lstnew(new_str);
	if (!new_node)
		return (ST_ERR_MALLOC);
	if (vars)
		ft_lstadd_back(vars, new_node);
	else
		*vars = new_node;
	return (ST_OK);
}

t_bool	valid_env_varname_syntax(char *str, int len)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (FALSE);
	i = 1;
	while (str[i] && i < len)
	{
		if (!ft_isalnum(str[i]) || str[i] == '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static t_state	bi_export_loop(t_list **vars, char *str, int len)
{
	t_state	state;
	t_list	*tmp;

	state = ST_OK;
	if (vars)
		tmp = check_env_var(str, len, *vars);
	else
		tmp = NULL;
	if (!tmp)
	{
		if (valid_env_varname_syntax(str, len))
			state = bi_export_new_var(vars, str);
		else
			return (bi_err_mng(6, "export", str), ST_ERR);
	}
	else
		state = bi_export_new_env_var_value(&tmp, str);
	return (state);
}

int	builtin_export(t_env *mini_env, char **cmmd)
{
	int		j;
	int		len;
	int		rt_val;
	t_state	state;

	j = 1;
	rt_val = ST_OK;
	if (!cmmd[1])
		return (builtin_export_print(mini_env));
	while (cmmd[j])
	{
		len = env_key_len(cmmd[j], '=');
		state = bi_export_loop(&mini_env->vars, cmmd[j], len);
		if (state == ST_ERR_MALLOC)
			return (ST_ERR_MALLOC);
		else if (state == ST_ERR)
			rt_val = ST_ERR;
		j++;
	}
	return (rt_val);
}
