/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 03:36:29 by faguirre          #+#    #+#             */
/*   Updated: 2025/10/03 17:22:19 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void	free_cmmd_node(void *ptr)
{
	int		i;
	t_cmmd	*cmmd;

	cmmd = (t_cmmd *)ptr;
	if (cmmd->cmmd)
	{
		i = -1;
		while (cmmd->cmmd[++i])
			free(cmmd->cmmd[i]);
		free(cmmd->cmmd);
		cmmd->cmmd = NULL;
	}
	if (cmmd->redir)
	{
		i = -1;
		while (cmmd->redir[++i].file)
			free(cmmd->redir[i].file);
		free(cmmd->redir);
		cmmd->redir = NULL;
	}
}

static void	print_cmmd(t_cmmd *cmmd)
{
	int	i;

	printf("\t- cmmd:");
	i = -1;
	while (cmmd->cmmd && cmmd->cmmd[++i])
		printf(" %s", cmmd->cmmd[i]);
	printf("\n");
	printf("\t- redir:");
	i = -1;
	while (cmmd->redir && cmmd->redir[++i].file)
	{
		if (cmmd->redir[i].type == DIR_IN)
			printf(" <");
		else if (cmmd->redir[i].type == DIR_OUT)
			printf(" >");
		else if (cmmd->redir[i].type == APPEND)
			printf(" >>");
		else if (cmmd->redir[i].type == HEREDOC)
			printf("<<");
		else
			printf("error symbol redir");
		printf("%s", cmmd->redir[i].file);
	}
	printf("\n");
}

void	print_lst_cmmd(t_list *lst_cmmd)
{
	t_cmmd	*cmmd;

	while (1)
	{
		printf("NODE\n");
		cmmd = (t_cmmd *)(lst_cmmd->content);
		print_cmmd(cmmd);
		if (!lst_cmmd->next)
			break ;
		lst_cmmd = lst_cmmd->next;
	}
}
