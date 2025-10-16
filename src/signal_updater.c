/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_updater.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:34:53 by faguirre          #+#    #+#             */
/*   Updated: 2025/10/16 12:34:55 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

int	update_heredoc(t_env *env, t_list *lst_cmmd)
{
	if (g_signal == SIGINT)
	{
		env->r = 128 + g_signal;
		close_heredocs(lst_cmmd);
		return (0);
	}
	return (1);
}

void	update_r(t_env *env)
{
	if (g_signal == SIGINT || g_signal == SIGQUIT)
		env->r = 128 + g_signal;
}
