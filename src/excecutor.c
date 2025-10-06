/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excecutor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 03:35:00 by faguirre          #+#    #+#             */
/*   Updated: 2025/10/06 13:51:13 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"


int	excecutor(t_list *lst_cmmd, t_env *tenv)
{
	if (!create_heredocs(lst_cmmd, tenv))
		return (0);
	correct_cmmd_namepath(lst_cmmd, tenv);
	if (!exec_cmmd(lst_cmmd, tenv))
	{
		close_heredocs(lst_cmmd);
		return (1);
	}
	close_heredocs(lst_cmmd);
	return (0);
}
