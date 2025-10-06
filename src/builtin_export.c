/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:49:26 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/06 14:46:32 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

int	declare_print(char **env_arr)
{
	int		j;
	char	**tmp;

	if (!env_arr)
		return (1);
	j = 0;
	tmp = env_arr;
	while (env_arr[j])
		printf("declare -x %s\n", tmp[j++]);
	return (0);
}

void	ft_sort_ascii(char **env_arr, int count)
{
	int	i;
	int	j;

	j = 0;
	while (j < count)
	{
		i = j + 1;
		while (i < count)
		{
			if (ft_strcmp(env_arr[j], env_arr[i]) > 0)
				ft_swap_str(&env_arr[j], &env_arr[i]);
			i++;
		}
		j++;
	}
}

int	builtin_export_print(t_env	*mini_env)
{
	int		count;
	char	**tmp;

	count = ft_lstsize(mini_env->vars);
	tmp = env_to_array(mini_env);
	if (!tmp)
		return (-1);
	ft_sort_ascii(tmp, count);
	declare_print(tmp);
	ft_free_2p(tmp);
	return (0);
}

t_state	new_env_var_value_bi_export(t_list **node, char *str)
{
	char	*tmp;
	char	*dup;

	tmp = (char *)(*node)->content;
	dup = ft_strdup(str);
	if (!dup)
		return (ST_ERR);
	ft_swap_str(&tmp, &dup);
	free(tmp);
	return (0);
}

t_state	new_var_bi_export(t_list **vars, char *str)
{
	char	*dup;
	t_list	*new_node;

	dup = ft_strdup(str);
	if (!dup)
		return (ST_ERR);
	new_node = ft_lstnew(dup);
	if (!new_node)
		return (malloc_err(), ST_ERR);
	ft_lstadd_back(vars, new_node);
	return (0);
}

t_bool	valid_env_varname_syntax(char *str, int len)
{
	int	i;

	if (!ft_isalpha(str[0]))
		return (FALSE);
	i = 0;
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

	state = 0;
	tmp = check_env_var(str, len, *vars);
	if (!tmp)
	{
		if (valid_env_varname_syntax(str, len))
			state = new_var_bi_export(vars, str);
		else
			return (-1);
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
	rt_val = 0;
	if (!cmmd[1])
		return (builtin_export_print(mini_env));
	while (cmmd[j])
	{
		len = env_key_len(cmmd[j], '=');
		state = bi_export_loop(&mini_env->vars, cmmd[j], len);
		if (state == ST_ERR)
			return (malloc_err(), -1);
		else if (state == -1)
			rt_val = 1;
		j++;
	}
	return (rt_val);
}
