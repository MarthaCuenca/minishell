/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:29:35 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/19 19:02:47 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	builtin_unset(t_env *mini_env, char **cmmd)
{
	int		j;
	int		len;
	int		state;
	t_list	*tmp;

	if (!cmmd[1])
		return (0);
	j = 0;
	state = 0;
	while (cmmd[j])
	{
		len = ft_strlen(cmmd[j]);
		tmp = check_env_var(cmmd[j], len, mini_env->vars);
		if (tmp)
			ft_lstunlink(&mini_env->vars, tmp, del_char_ptr);
		else
			state = 1;
		j++;
	}
	return (state);
}
