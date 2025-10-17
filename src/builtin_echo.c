/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 10:02:10 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/11 19:34:20 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

int	is_less_n(char **cmmd)
{
	int	j;
	int	i;

	j = 1;
	while (cmmd[j])
	{
		if (cmmd[j][0] && cmmd[j][0] == '-' && cmmd[j][1] && cmmd[j][1] == 'n')
		{
			i = 2;
			while (cmmd[j][i] && cmmd[j][i] == 'n')
				i++;
			if (cmmd[j][i] && cmmd[j][i] != 'n')
				return (j);
		}
		else
			return (j);
		j++;
	}
	return (j);
}

int	builtin_echo(t_cmmd *nd)
{
	int		j;
	char	**tmp;
	t_bool	new_line;

	tmp = nd->cmmd;
	new_line = is_less_n(tmp);
	if (!tmp[1])
		return (printf("\n"), 0);
	else if (new_line - 1 && !tmp[2])
		return (0);
	j = new_line;
	printf("%s", tmp[j++]);
	while (tmp[j])
		printf(" %s", tmp[j++]);
	if (!(new_line - 1))
		printf("\n");
	return (0);
}
