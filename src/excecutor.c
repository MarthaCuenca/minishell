/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excecutor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 03:35:00 by faguirre          #+#    #+#             */
/*   Updated: 2025/10/06 11:54:34 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"


int	excecutor(t_list *lst_cmmd, t_env *tenv)
{
	create_heredocs(lst_cmmd);
	correct_cmmd_namepath(lst_cmmd);
	if (!exec_cmmd(lst_cmmd, tenv))
	{
		close_heredocs(lst_cmmd);
		return (1);
	}
	close_heredocs(lst_cmmd);
	return (0);
}
