/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:00:50 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/10 11:44:04 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int	check_arg_bi_exit(char **cmmd)
{
	int	num;

	if (cmmd[2])
		return (127);
	else if (!ft_str_isdigit(cmmd[1]) || is_overflow(cmmd[1]))
		return (2);
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

	status = 0;
	tmp = nd;
	//cambiar por la funcion de Cesc
	if (tmp->cmmd[1])
		status = check_arg_bi_exit(tmp->cmmd);
	clean_mng(mini_env, NULL, NULL, pars);
	exit(status);
}
