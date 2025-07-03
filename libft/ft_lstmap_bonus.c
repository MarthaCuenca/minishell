/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:37:26 by faguirre          #+#    #+#             */
/*   Updated: 2024/09/19 17:04:53 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*temp;

	if (!lst)
	{
		return ((void *)0);
	}
	result = ft_lstnew(f(lst->content));
	if (!result)
	{
		return ((void *)0);
	}
	while (lst->next)
	{
		lst = lst->next;
		temp = ft_lstnew(f(lst->content));
		if (!temp)
		{
			ft_lstclear(&result, del);
			return ((void *)0);
		}
		ft_lstadd_back(&result, temp);
	}
	return (result);
}
