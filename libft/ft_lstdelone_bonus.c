/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:20:41 by faguirre          #+#    #+#             */
/*   Updated: 2025/08/06 18:53:52 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
}

void	ft_lstunlink(t_list **lst, t_list *nd_rm, void (*del)(void *))
{
	t_list *prev;	
	t_list *next;	

	if (!*lst || !nd_rm) 
		return ;
	if (ft_lstsize(*lst) <= 2)
	{
		if (*lst == nd_rm)
			*lst = nd_rm->next;
		else
			(*lst)->next = NULL;
		return (ft_lstdelone(nd_rm, del));
	}
	next = nd_rm->next;
	if (*lst != nd_rm)
	{	
		prev = *lst;
		while (prev->next != nd_rm)
			prev = prev->next;
		prev->next = next;
	}
	ft_lstdelone(nd_rm, del);
}
