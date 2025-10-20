/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:49:26 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/19 19:10:22 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	declare_print(char **env_arr)
{
	int		j;
	char	**tmp;

	j = 0;
	tmp = env_arr;
	while (env_arr[j])
		printf("declare -x %s\n", tmp[j++]);
}

void	ft_sort_ascii(char **env_arr, int count)
{
	int	i;
	int	j;
	int	len;

	j = 0;
	while (j < count)
	{
		i = j + 1;
		len = env_key_len(env_arr[j], '=');
		while (i < count)
		{
			if (ft_strncmp(env_arr[j], env_arr[i], len) > 0)
				ft_swap_str(&env_arr[j], &env_arr[i]);
			i++;
		}
		j++;
	}
}

t_state	builtin_export_print(t_env	*mini_env)
{
	int		count;
	char	**tmp;

	count = ft_lstsize(mini_env->vars);
	tmp = env_to_array(mini_env);
	if (!tmp)
		return (ST_ERR_MALLOC);
	ft_sort_ascii(tmp, count);
	declare_print(tmp);
	ft_free_2p(tmp);
	return (ST_OK);
}

t_state	new_env_var_value_bi_export(t_list **node, char *str)
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

t_state	new_var_bi_export(t_list **vars, char *str)
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

t_state	bi_export_loop(t_list **vars, char *str, int len)
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
			state = new_var_bi_export(vars, str);
		else
			return (ST_ERR);
	}
	else
		state = new_env_var_value_bi_export(&tmp, str);
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
