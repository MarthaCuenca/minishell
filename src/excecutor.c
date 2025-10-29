/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excecutor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 03:35:00 by faguirre          #+#    #+#             */
/*   Updated: 2025/10/29 17:18:24 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// Return 1 if not malloc fail.
int	excecutor(t_list *lst_cmmd, t_env *tenv)
{
	int	status_r;

	setup_signal_heredoc();
	if (create_heredocs(lst_cmmd, tenv))
	{
		if (correct_cmmd_namepath(lst_cmmd, tenv))
		{
			setup_signal_standard(SIG_IGN, SIG_IGN);
			exec_cmmd(lst_cmmd, tenv);
		}
	}
	close_heredocs(lst_cmmd);
	status_r = tenv->r;
	tenv->r = fix_exit(tenv->r);
	if (status_r == -1)
		return (0);
	return (1);
}
