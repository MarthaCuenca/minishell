/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excecutor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 03:35:00 by faguirre          #+#    #+#             */
/*   Updated: 2025/10/13 07:44:54 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// Return 1 if not malloc fail.
int	excecutor(t_list *lst_cmmd, t_env *tenv)
{
	if (create_heredocs(lst_cmmd, tenv))
		if (correct_cmmd_namepath(lst_cmmd, tenv))
		{
			setup_signal_parent();
			exec_cmmd(lst_cmmd, tenv);
		}
	close_heredocs(lst_cmmd);
	if (tenv->r == -1)
		return (0);
	
	return (1);
}
