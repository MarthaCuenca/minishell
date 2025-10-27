/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:00:50 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/27 13:11:16 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

static int	bi_exit_check_arg(char **cmmd)
{
	int	num;

	if (cmmd[2])
		return (1);
	else if (!ft_str_isdigit(cmmd[1]) || is_overflow(cmmd[1]))
		return (bi_err_mng(5, cmmd[0], cmmd[1]), 2);
	else
		num = ft_atoi(cmmd[1]);
	if (num > 255)
		num = num % 256;
	return (num);
}

void	builtin_exit(t_env *mini_env, t_list **pars, t_cmmd *nd)
{
	int		status;
	t_cmmd	*tmp;

	status = mini_env->r;
	tmp = nd;
	if (tmp->cmmd[1])
	{
		if (tmp->cmmd[2])
			return (bi_err_mng(1, tmp->cmmd[0], NULL));
		else
			status = bi_exit_check_arg(tmp->cmmd);
	}
	clean_mng(mini_env, NULL, NULL, pars);
	exit(status);
}
