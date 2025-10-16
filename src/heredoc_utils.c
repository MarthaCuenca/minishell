/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:04:14 by faguirre          #+#    #+#             */
/*   Updated: 2025/10/16 14:04:16 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

char	*create_filename(char *str_name, int counter, t_env *env)
{
	char	*filename;
	char	*str_num;

	str_num = ft_itoa(counter);
	if (!str_num)
		return (get_error_chr(env, ST_ERR_MALLOC, NULL));
	filename = ft_strjoin(str_name, str_num);
	if (!filename)
		return (get_error_chr(env, ST_ERR_MALLOC, NULL));
	free(str_num);
	return (filename);
}

void	close_heredocs(t_list *lst_cmmd)
{
	int		i;
	t_cmmd	*cmmd;

	while (lst_cmmd)
	{
		cmmd = (t_cmmd *)lst_cmmd->content;
		i = -1;
		while (cmmd->redir[++i].file)
			if (cmmd->redir[i].type == HEREDOC)
				if (access(cmmd->redir[i].file, F_OK) == 0)
					unlink(cmmd->redir[i].file);
		lst_cmmd = lst_cmmd->next;
	}
}
