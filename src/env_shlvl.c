/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:13:20 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/25 18:21:15 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*increase_shell_level(char *shell_var)
{
	long int	lvl;
	char		b[12];
	char		*new_lvl;

	if (shell_var == NULL || (shell_var && is_overflow(shell_var)))
		lvl = 0;
	else
	{
		lvl = ft_atoi(shell_var + 6);
		if (lvl + 1 > 2147483647 || lvl < 0)
			lvl = 0;
		else
			lvl++;
	}
	ft_static_itoa(b, 12, lvl);
	new_lvl = ft_strjoin("SHLVL=", b);
	if (!new_lvl)
		return (malloc_err(), NULL);
	return (new_lvl);
}

t_list	*is_not_shlvl(t_list **head, t_bool *shlvl_founded)
{
	t_list	*new_nd;
	char	*shlvl;

	shlvl = create_content_env_nd(NULL, 0, shlvl_founded);
	if (!shlvl)
		return (NULL);
	new_nd = ft_lstnew(shlvl);
	if (!new_nd)
		return (ft_lstclear(&new_nd, del_char_ptr), NULL);
	if (!*head)
		*head = new_nd;
	else
		ft_lstadd_back(head, new_nd);
	return (new_nd);
}
