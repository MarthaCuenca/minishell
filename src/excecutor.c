/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excecutor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 03:35:00 by faguirre          #+#    #+#             */
/*   Updated: 2025/10/03 18:08:38 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"


int	excecutor(t_list *lst_cmmd, t_env *tenv)
//int	main(int argc, char **argv, char **env)
{
	/*t_list	*lst_cmmd;
	t_env	tenv;

	if (argc < 2)
		return (1);
	tenv.vars = env;
	tenv.r = 0;
	lst_cmmd = init_lst_cmmd(argv);*/
	create_heredocs(lst_cmmd);
	correct_cmmd_namepath(lst_cmmd);
	if (!exec_cmmd(lst_cmmd, tenv))
	{
		close_heredocs(lst_cmmd);
		return (1);
	}
	//ft_printf("$?: %d\n", tenv.r);
	close_heredocs(lst_cmmd);
	//ft_lstclear(&lst_cmmd, free_cmmd_node);
	return (0);
}
