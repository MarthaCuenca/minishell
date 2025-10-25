/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 19:42:17 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/24 19:50:02 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_state	oldpwd_path(t_env *mini_env, char **result)
{
	char	*value;

	value = obtain_env_var_value(mini_env, NULL, "OLDPWD");
	if (!value || (value && value[0] == '\0'))
		return (bi_err_mng(2, "cd", "OLDPWD"), ST_ERR);
	*result = ft_strdup(value);
	if (!*result)
		return (ST_ERR_MALLOC);
	return (ST_OK);
}

char	*home_path_result(char *match, char *ptr)
{
	char	*tmp;

	if (ptr)
		tmp = ft_strjoin(match, ptr);
	else
		tmp = ft_strdup(match);
	if (!tmp)
		return (NULL);
	return (tmp);
}

t_state	home_path(t_env *mini_env, char *cmmd, char **result)
{
	char	*ptr;
	char	*value;

	value = obtain_env_var_value(mini_env, NULL, "HOME");
	if (!value || (value && value[0] == '\0'))
		return (bi_err_mng(2, "cd", "HOME"), ST_ERR);
	ptr = NULL;
	if (cmmd && cmmd[0] && cmmd[1] && cmmd[1] != '/')
		return (ST_ERR);
	else if (cmmd && cmmd[0] && cmmd[1] && cmmd[1] == '/')
		ptr = &cmmd[1];
	*result = home_path_result(value, ptr);
	if (!*result)
		return (ST_ERR_MALLOC);
	return (ST_OK);
}

t_state	check_path(t_env *mini_env, char *cmmd, char **result)
{
	t_state	state;

	state = ST_OK;
	if (cmmd == NULL || (cmmd && cmmd[0] == '~'))
		state = home_path(mini_env, cmmd, result);
	else if (cmmd && cmmd[0] == '-' && !cmmd[1])
		state = oldpwd_path(mini_env, result);
	else
	{
		*result = ft_strdup(cmmd);
		if (!*result)
			state = ST_ERR_MALLOC;
	}
	return (state);
}
