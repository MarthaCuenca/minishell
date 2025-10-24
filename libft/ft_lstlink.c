/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlink.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:57:05 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/24 17:32:23 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstlink(t_list **anchor, t_list *add)
{
	t_list	*next;
	t_list	*add_last;

	if (!*anchor || !add)
		return ;
	next = (*anchor)->next;
	(*anchor)->next = add;
	add_last = ft_lstlast(add);
	add_last->next = next;
}

void	ft_lstunlink(t_list **lst, t_list *nd_rm, void (*del)(void *))
{
	t_list	*prev;	
	t_list	*next;	

	if (!*lst || !nd_rm)
		return ;
	if (ft_lstsize(*lst) <= 2 || nd_rm == *lst)
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
		while (prev->next && prev->next != nd_rm)
			prev = prev->next;
		prev->next = next;
	}
	ft_lstdelone(nd_rm, del);
}
