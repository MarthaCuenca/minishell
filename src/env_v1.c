/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_v1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:02:15 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/09/19 14:02:53 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"
#include "libft.h"

void	ft_2p_free(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

char	**ft_p2_dup(char **arr_ori)
{
	int		i;
	int		j;
	char	**cp;

	if (!arr_ori)
		return (NULL);
	i = 0;
	j = 0;
	while (arr_ori[j] != NULL)
		j++;
	cp = malloc((j + 1) * sizeof(char *));
	while (i < j)
	{
		cp[i] = ft_strdup(arr_ori[i]);
		if (!cp[i])
			ft_2p_free(cp);
		i++;
	}
	cp[i] = NULL;
	return (cp);
}

char	**ft_env_dup(char **env_ori)
{
	char	**env_cp;

	if (!env_ori)
		return (NULL);
	env_cp = ft_p2_dup(env_ori);
	if (!env_cp)
		return (NULL);
	return (env_cp);
}
